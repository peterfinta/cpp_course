#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>


struct DYNPoint 
{
	std::vector<float> data;

	// We use a static function to return a DYNPoint object (this pattern is
  // sometimes called a "factory method")
	// We can mark functions as nodiscard to indicate that we must use
  // the return value in some way (e.g, it doesn't get discarded as ).
	[[nodiscard]] static DYNPoint createRandomPoint(unsigned int size
                                                 ,int minimum=-5000
                                                 ,int maximum=5000)
  {
		DYNPoint p;
    float resizeFactor = (float)(maximum - minimum) / (float)RAND_MAX;
		if (size > 0 && minimum <= maximum)
    {			
      for(int i = 0; i < size; i++)
        p.data.push_back(((float)std::rand() * resizeFactor) + (float)minimum);
		}
		return p;
	}
};

struct KNN 
{
	KNN(float(*_function_ptr_Distance)(const DYNPoint &, const DYNPoint &))
		: function_ptr_Distance(_function_ptr_Distance)
	{
	}

	std::vector<std::pair<DYNPoint, unsigned int>> trainingData{}; // default initialize on creation

	float(*function_ptr_Distance)(const DYNPoint &, const DYNPoint &) = 0;

	// just sets the training data (no actual training required)
	void TrainKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset)
  {
		trainingData.clear();
		trainingData = dataset;
	}

	int classify(const unsigned int k, const DYNPoint &A) const
  {

		int class_label = -1;

		if (k && function_ptr_Distance && trainingData.size())
    {
      std::vector<std::pair<float, int>> distancesAndLabels{};
      for(auto it = trainingData.begin(); it != trainingData.end(); it++)
      {
        distancesAndLabels.emplace_back(it->second
                                       ,function_ptr_Distance(it->first, A));
      }

      std::sort(distancesAndLabels.begin()
               ,distancesAndLabels.end()
               ,[](auto a, auto b){return a.first < b.first;});

      std::multimap<int, int> labelsMap{};

      class_label = distancesAndLabels.at(0).second;
      for(int i = 0; i < k; i++)
      {
        int idx = distancesAndLabels.at(i).second;
        labelsMap.emplace(idx, 1);
        if(labelsMap.count(idx) > labelsMap.count(class_label))
          class_label = idx; 
      }
			// STUDENT TODO: your code
		}
		return class_label;
	}
};

float DistanceManhattan(const DYNPoint &A, const DYNPoint &B)
{
  if(A.data.size() != B.data.size()) return -1.0f;
  float res = 0.0f;
  for(auto itA = A.data.begin(), itB = B.data.begin();
      itA != A.data.end(); ++itA, ++itB) res += std::abs(*itA - *itB);

	return res / (float)A.data.size();
}

float DistanceEuclid(const DYNPoint &A, const DYNPoint &B)
{
  if(A.data.size() != B.data.size()) return -1.0f;
  float res = 0.0f;
  for(auto itA = A.data.begin(), itB = B.data.begin();
      itA != A.data.end(); ++itA, ++itB) res += std::pow(*itA - *itB, 2.0f);

	return std::sqrt(res / (float)A.data.size());
}

void createDataset(std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const unsigned int amount, const unsigned int class_label,
				const unsigned int point_size, const int minimum, const int maximum) {

	if (amount > 0 && point_size>0 && minimum <= maximum) {
    for(unsigned i = 0; i < amount; i++)
    {
      std::pair<DYNPoint, unsigned> newData(DYNPoint::createRandomPoint(point_size
                                                                       ,minimum
                                                                       ,maximum)
                                           , class_label);
      dataset.push_back(newData);
    }

	// STUDENT TODO: your code

	}
}

void evaluateKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const KNN &Classifier, const unsigned int k) {
	if (!dataset.empty()) {
		float acc = 0;
		for (size_t i = 0; i < dataset.size(); i++) {
			if (static_cast<unsigned int>(Classifier.classify(k, dataset[i].first)) == dataset[i].second)
				acc++;
		}
		std::cout << "Accuracy: " << acc / float(dataset.size()) << std::endl;
	}
}









