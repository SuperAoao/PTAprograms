#include <iostream>
#include <vector>

using namespace std;

// 在线处理方法
int onlineProcess(const std::vector<int>& dataVector)
{
	int maxSubsqeSum = 0;
	int currentSubsqeSum = 0;
	for (int i = 0; i < dataVector.size(); i++)
	{
		currentSubsqeSum += dataVector.at(i);
		if (currentSubsqeSum < 0)
		{
			currentSubsqeSum = 0;
		}
		else
		{
			if(maxSubsqeSum < currentSubsqeSum)
			maxSubsqeSum = currentSubsqeSum ;
		}
	}
	return maxSubsqeSum;
}

int main()
{
	int k;
	std::vector<int> dataset;
	cin >> k;
	dataset.resize(k);
	for (int i = 0; i < k; i ++)
	{
		auto iter = dataset.begin();
		iter += i;
		cin >> (*iter);
	}

	/*输出测试*/
	//cout << k;
	//for (auto iter = dataset.begin(); iter != dataset.end(); iter++)
	//{
	//	cout<< (*iter);
	//}
	cout << onlineProcess(dataset);
	return 0;
}