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


/*1. 一个二维数组，每行按递增序列排列，每列也按递增序列排列，
* 完成一个函数，输入一个整数， 判断二维数组中是否含有该整数*/
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

/*2. 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
* 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素*/
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
			
			// 左指针向右移动，如果右边的值比当前值大或者相等
			if(rotateArray[left] <= rotateArray[left+1){
				left = left + 1;
			}
			else{
				// 如果右边的值小于左指针指向的值，则右边是旋转前的第一个值
				return rotateArray[left+1];
			}
			
			// 右指针向左移动，如果左边的值小于或等于右指针指向的值
			if(rotateArray[right-1] <= rotateArray[right]){
				right = right - 1;
			}else{
				return rotateArray[right];   // 右指针指向的值小于左临的值，说明当前right是最小值
			}

		}

		return rotateArray[left];
	}
};

/*3. 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，
并保证奇数和奇数，偶数和偶数之间的相对位置不变*/
class Solution3{
public:
	void reOrderArray(vector<int> & array){
		deque<int> result;
		int num = array.size();
		for(int i=0; i<num; i++){
			// 奇数在前从小到大排列，则需要从大往小的顺序放进队列
			if(array[num-i-1]%2 == 1){
				result.push_front(array[num-i-1]);
			}
			
			// 偶数放在队列尾，则可以从小到大的顺序排列放进队列
			if(array[array[i]%2 == 0){
				result.push_back(array[i]);
			}
		}
		array.assign(result.begin(), result.end());
	}
};


/*4. 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字*/
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


/*5. 连续子数组的最大和*/
class Solution5{
public:
	int FindGreatestSumOfSubArray(vector<int> array){
		int size = array.size();
		if(size == 0){
			return 0;
		}

		// 初始化变量， maxSum为最大和， curSum为当前和
		int maxSum = array[0];
		int curSum = array[0];

		for(int i = 1; i<size; i++){
			if(curSum <= 0){
				// 当前和不大于0， 则重新开始计数起点
				curSum = array[i];
			}else{
				// 当前和大于0，则继续累加
				curSum += array[i];
			}

			if(curSum > maxSum){
				maxSum = curSum;
			}
		}
		return maxSum;
	}
};


/*6. 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个*/
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


/*7. 在数组中的两个数字，如果前面一个数字大于后面的数字，
则这两个数字组成一个逆序对。输入一个数组,求出这个数组中
的逆序对的总数P并将P对1000000007取模的结果输出********/
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
		// 如果起始与终止指向同一个位置，则没有逆序对
		if(begin == end){
			return 0;
		}

		int mid = (begin+end) >> 1;

		// 递归左半段
		long leftCount = InversePairsCore(backup, data, begin, mid);

		// 递归右半段
		long rightCount = InversePairsCore(backup, data, mid+1, end);

		int i = mid;  // 初始化左半段最后一个数的下标
		int j = end;  // 初始化右半段最后一个数的下标
		int backupIndex = end; // 辅助数组复制的数组的最后一个数的下标
		long count = 0;  // 计数，逆序对的个数

		while(i>=begin && j>mid){
			if(data[i] > data[j]){
				backup[backupIndex--] = data[i--];
				count += j-mid;
			}
			else{
				backup[backupIndex--] = data[j--];
			}
		}

		// 将数组中剩余的，非逆序对成员的数组元素复制到辅助数组中
		for(;i>=begin; i--){
			backup[backupIndex--] = data[i];
		}

		for(; j>mid; j--){
			backup[backupIndex--] = data[j];
		}

		return leftCount+rightCount+count;
	}
};

/*8. 统计一个数字在有序数组中出现的次数*/
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
				// 向左搜索，求第一个该数的下标
				if(begin == firstOrEndIndex){
					if((midIndex>0 && data[midIndex-1]<k) || (midIndex == 0)){
						return midIndex;
					}else{
						end = midIndex - 1;
					}
				}
				// 向右搜索，求最后一个该数的下标
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

			// 更新中间下标，和中间值
			midIndex = (begin+end)>>1;
			midData = data[midIndex];
			
		}
		return -1;
	}

};

/*9. 一个整数型数组里除了两个数字之外，其他的数字都出现了两次。
找出两个只出现一次的数字要求时间复杂度是O(n), 空间复杂度是O(1)*/
class Solution9{
public:
	void FindNumsAppearOnce(vector<int> array, int *num1, int *num2)
	{
		int size = array.size();
		if(size < 2){
			return;
		}

		// 求数组所有元素异或的结果
		int resultExclusiveOR = 0;

		for(int i=0; i<size; i++){
			resultExclusiveOR ^= array[i];
		}

		// 找出异或值第一个1的位数
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


/*10. 在一个长度为n的数组里的所有数字都在0到n-1的范围内。?
******数组中某些数字是重复的，但不知道有几个数字是重复的。
*也不知道每个数字重复几次。请找出数组中任意一个重复的数字*/
class Solution10{
public:
	bool duplicate(int numbers[], int *duplication)
	{
		int index = -1;
		int length = strlen(numbers);
		// 非法输入
		if(numbers==NULL){
			return false;
		}

		// 非法输入
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
/*11.给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],
其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。不能使用除法*/
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

