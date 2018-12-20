#include <stdio.h>
#include <queue>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "stdafx.h"
#include "class.h"
#include <iostream>


/*1. һ����ά���飬ÿ�а������������У�ÿ��Ҳ�������������У�
* ���һ������������һ�������� �ж϶�ά�������Ƿ��и�����*/
class Soultion1{
public:
	bool find(int target, vector<vector<int>> array){
		int rows = array.size();
		int cols = array[0].size();

		if(!array.empty() && rows > 0 && cols >0){
			int row = 0;
			int col = cols - 1;
			while (row < rows && col >=0){
				if(array[row][col] == target){
					return true;
				}else if(array[row][col] < target){
					row++;
				}else{
					col--;
				}
			}
		}
		return false;
	}
};

/*2. ��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
* ����һ���ǵݼ�����������һ����ת�������ת�������СԪ��*/
class Solution2{
public:
	int minElementInRotateArray(vector<int> rotateArray)
	{
		int size = rotateArray.size();
		if(size == 0){
			return 0;
		}
		int left = 0;
		int right = size - 1;

		while(left < right){
			
			// ��ָ�������ƶ�������ұߵ�ֵ�ȵ�ǰֵ��������
			if(rotateArray[left] <= rotateArray[left+1){
				left = left + 1;
			}
			else{
				// ����ұߵ�ֵС����ָ��ָ���ֵ�����ұ�����תǰ�ĵ�һ��ֵ
				return rotateArray[left+1];
			}
			
			// ��ָ�������ƶ��������ߵ�ֵС�ڻ������ָ��ָ���ֵ
			if(rotateArray[right-1] <= rotateArray[right]){
				right = right - 1;
			}else{
				return rotateArray[right];   // ��ָ��ָ���ֵС�����ٵ�ֵ��˵����ǰright����Сֵ
			}

		}

		return rotateArray[left];
	}
};

/*3. ����һ���������飬ʵ��һ�����������������������ֵ�˳��
ʹ�����е�����λ�������ǰ�벿�֣����е�ż��λ��λ������ĺ�벿�֣�
����֤������������ż����ż��֮������λ�ò���*/
class Solution3{
public:
	void reOrderArray(vector<int> & array){
		deque<int> result;
		int num = array.size();
		for(int i=0; i<num; i++){
			// ������ǰ��С�������У�����Ҫ�Ӵ���С��˳��Ž�����
			if(array[num-i-1]%2 == 1){
				result.push_front(array[num-i-1]);
			}
			
			// ż�����ڶ���β������Դ�С�����˳�����зŽ�����
			if(array[array[i]%2 == 0){
				result.push_back(array[i]);
			}
		}
		array.assign(result.begin(), result.end());
	}
};


/*4. ��������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬���ҳ��������*/
class Solution4{
public:
	int moreThanHalfNum(vector<int> array){
		if(array.size() == 0){
			return 0;
		}

		int result = array[0];
		int times = 1;
		for(int i = 1; i<array.size(); i++){
			if(0 == times){
				result = array[i];
				times = 1;
			}else if(result == array[i){
				times++;
			}else{
				times--;
			}
		}
		
		times = 0;
		for(int i=0; i<array.size(); i++){
			if(result == array[i]){
				times++;
			}
		}
		
		return (times>(array.size()>>1))?result:0;
	}
};


/*5. ���������������*/
class Solution5{
public:
	int FindGreatestSumOfSubArray(vector<int> array){
		int size = array.size();
		if(size == 0){
			return 0;
		}

		// ��ʼ�������� maxSumΪ���ͣ� curSumΪ��ǰ��
		int maxSum = array[0];
		int curSum = array[0];

		for(int i = 1; i<size; i++){
			if(curSum <= 0){
				// ��ǰ�Ͳ�����0�� �����¿�ʼ�������
				curSum = array[i];
			}else{
				// ��ǰ�ʹ���0��������ۼ�
				curSum += array[i];
			}

			if(curSum > maxSum){
				maxSum = curSum;
			}
		}
		return maxSum;
	}
};


/*6. ����һ�����������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ���������������С��һ��*/
class Solution6{
public:
	string printMinNumber(vector<int> array){
		int size = array.size();
		if(size == 0){
			return "";
		}
		string res;
		sort(array.begin(), array.end(), cmp);
		for(int i=0; i<length; i++){
			res += to_string(array[i]);
		}

		return res;
	}

private:
	static bool cmp(int a, int b){
		string A = to_string(a) + to_string(b);
		string B = to_string(b) + to_string(a);
		return A<B;
	}
};


/*7. �������е��������֣����ǰ��һ�����ִ��ں�������֣�
���������������һ������ԡ�����һ������,������������
������Ե�����P����P��1000000007ȡģ�Ľ�����********/
class Solution7{
public:
	int InversePairs(vector<int> data)
	{
		int size = data.size();
		
		if(0 == size){
			return 0;
		}
		vector<int> backup;
		for(int i=0; i<size; i++){
			backup.push_back(data[i]);
		}
		return InversePairsCore(data, backup, 0, size-1);
	}

private:
	long InversePairsCore(vector<int> &data, vector<int> &backup, int begin, int end)
	{
		// �����ʼ����ָֹ��ͬһ��λ�ã���û�������
		if(begin == end){
			return 0;
		}

		int mid = (begin+end) >> 1;

		// �ݹ�����
		long leftCount = InversePairsCore(backup, data, begin, mid);

		// �ݹ��Ұ��
		long rightCount = InversePairsCore(backup, data, mid+1, end);

		int i = mid;  // ��ʼ���������һ�������±�
		int j = end;  // ��ʼ���Ұ�����һ�������±�
		int backupIndex = end; // �������鸴�Ƶ���������һ�������±�
		long count = 0;  // ����������Եĸ���

		while(i>=begin && j>mid){
			if(data[i] > data[j]){
				backup[backupIndex--] = data[i--];
				count += j-mid;
			}
			else{
				backup[backupIndex--] = data[j--];
			}
		}

		// ��������ʣ��ģ�������Գ�Ա������Ԫ�ظ��Ƶ�����������
		for(;i>=begin; i--){
			backup[backupIndex--] = data[i];
		}

		for(; j>mid; j--){
			backup[backupIndex--] = data[j];
		}

		return leftCount+rightCount+count;
	}
};

/*8. ͳ��һ�����������������г��ֵĴ���*/
class Solution8{
public:
	int CountKOfArray(vector<int> data, int k)
	{
		int size = data.size();
		if(size == 0){
			return 0;
		}
		int firstIdx = GetFirstOrEndKIndx(data, k, 0, size-1, 0);
		int endIdx = GetFirstOrEndKIndx(data, k, 0, size-1, size-1);

		if((firstIdx !=-1) && (endIdx != -1)){
			return endIdx - firstIdx + 1;
		}
		return 0;
	}
private:
	int GetFirstOrEndKIndx(vector<int> data, int k,  int begin, int end, int firstOrEndIndex)
	{
		int size = data.size();
		int midIndex = (begin + end) >> 2;
		int midData = data[midIndex];

		while(begin <= end){
			if(midData == k){
				// �������������һ���������±�
				if(begin == firstOrEndIndex){
					if((midIndex>0 && data[midIndex-1]<k) || (midIndex == 0)){
						return midIndex;
					}else{
						end = midIndex - 1;
					}
				}
				// ���������������һ���������±�
				else if(end == firstOrEndIndex){
					if((midIndex<size-1 && data[midIndex+1]>k) || (midIndex==size-1)){
						return midIndex;
					}else{
						begin = midIndex + 1;
					}
				}
				
			}
			else if(midData > k){
				end = midIndex - 1;
			}
			else{
				begin = midIndex + 1;
			}

			// �����м��±꣬���м�ֵ
			midIndex = (begin+end)>>1;
			midData = data[midIndex];
			
		}
		return -1;
	}

};

/*9. һ�������������������������֮�⣬���������ֶ����������Ρ�
�ҳ�����ֻ����һ�ε�����Ҫ��ʱ�临�Ӷ���O(n), �ռ临�Ӷ���O(1)*/
class Solution9{
public:
	void FindNumsAppearOnce(vector<int> array, int *num1, int *num2)
	{
		int size = array.size();
		if(size < 2){
			return;
		}

		// ����������Ԫ�����Ľ��
		int resultExclusiveOR = 0;

		for(int i=0; i<size; i++){
			resultExclusiveOR ^= array[i];
		}

		// �ҳ����ֵ��һ��1��λ��
		unsigned int indexBit = FindFirstBitIs1(resultExclusiveOR);

		*num1 = *num2 = 0;
		for(int j=0; j<size; j++){
			if(IsBit1(array[j],indexBit)){
				*num1 ^= array[j];
			}
			else{
				*num2 ^= array[j];
			}
		}
	}
private:
	unsigned int FindFirstBitIs1(int num)
	{
		unsigned int indexBit = 0;
		if((num & 1 == 0) && (indexBit < 8*sizeof(unsigned int))){
			num = num >> 1;
			indexBit++;
		}
		return indexBit;
	}

	bool IsBit1(int num, unsigned int indexBit)
	{
		num = num >> indexBit;
		return num & 1;
	}
};


/*10. ��һ������Ϊn����������������ֶ���0��n-1�ķ�Χ�ڡ�?
******������ĳЩ�������ظ��ģ�����֪���м����������ظ��ġ�
*Ҳ��֪��ÿ�������ظ����Ρ����ҳ�����������һ���ظ�������*/
class Solution10{
public:
	bool duplicate(int numbers[], int *duplication)
	{
		int index = -1;
		int length = strlen(numbers);
		// �Ƿ�����
		if(numbers==NULL){
			return false;
		}

		// �Ƿ�����
		for(int i=0; i<length; i++){
			if((numbers[i]<0) || (numbers[i]>i)){
				return false;
			}
		}

		for(int i=0; i<length; i++){
#if 1
			index = numbers[i];
			if(index > length)
			{
				index -= length;
			}
			if(numbers[index] >= length)
			{
				*duplication = index;
				return true;
			}
			numbers[index] += length;

#else
			while(numbers[i] != i){
				if(numbers[i] == numbers[numbers[i]]){
					return true;
				}
				swap(numbers[i], numbers[numbers[i]]);
			}
#endif
		}
		return false;
	}
};
/*11.����һ������A[0,1,...,n-1],�빹��һ������B[0,1,...,n-1],
����B�е�Ԫ��B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]������ʹ�ó���*/
class Solution11{
public:
	vector<int> multiply(vector<int> A)
	{
		int length = A.size();

		vector<int> B(length);

		if(length==0){
			return B;
		}

		// part1 top-->bottom
		B[0] = 1;
		for(int i=1; i<length; i++){
			B[i] = B[i-1]*A[i-1];
		}

		// part2 bottom->top
		int tmp = 1;
		for(int i=length-2; i>=0; i--){
			tmp *= A[i+1];
			B[i] *= tmp;
		}
		return B;
	}
};



void main()
{
  using namespace std;
  int array[8] = [2, 2, 1, 1, 3, 3, 5, 7];
  int num1, num2;
  Solution9::FindNumsAppearOnce(array, &num1, &num2);
  cout<<num1<<' '<< num2<<endl;
}

