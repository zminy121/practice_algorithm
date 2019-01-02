from collections import deque
import operator

"""1. 一个二维数组，每行按递增序列排列，每列也按递增序列排列，
* 完成一个函数，输入一个整数， 判断二维数组中是否含有该整数"""
"""
:param target:    int
:param matrix: [[]]
:return   :    bool
"""
class Solution1:
    def find_intger(target, matrix):
        if not matrix:
            return False

        #获取数组的行列数
        rows, cols = len(matrix), len(matrix[0])
        row = 0
        col = cols - 1
        while row < rows and col >= 0:
            if matrix[row][col] == target:
                return True
            elif matrix[row][col] < target:
                row += 1
            else:
                col -= 1

        return False


"""
2. 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
* 输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素
"""

class Solution2:
    def minElementInRotateArray(self, array):
        if not len(array):
            return 0
        left = 0
        right = len(array) - 1

        while left < right :
            if array[left] <= array[left+1]:
                left = left + 1
            else:
                return array[left+1]

            if array[right - 1] <= array[right]:
                right = right - 1
            else:
                return array[right]

        return array[left]


"""
3. 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，
并保证奇数和奇数，偶数和偶数之间的相对位置不变
"""

class Solution3:
    def __init__(self):
        pass

# 方法1 列表
    def reOrderByList(self, array):
        result = []
        index = len(array)
        for i in range(index):
            if array[index-i-1]%2 == 1:
                result.insert(0, array[index-i-1])

            if array[i]%2 == 0:
                result.append(array[i])

        return result

    #方法2 不开辟新空间
    def reOrderByOrig(self, array):
        newOrder = -1
        for idx in range(len(array)):
            if array[idx]%2 == 1:
                newOrder += 1
                array.insert(newOrder, array.pop(idx))
        return array

    #方法3 用队列
    def reOrderByDeque(self, array):
        odd = deque()
        length = len(array)
        for idx in range(length):
            if array[length - idx - 1]%2 == 1:
                odd.appendleft(array[length-idx-1])

            if array[idx] % 2 == 0:
                odd.append(array[idx])

        return list(odd)

"""
4. 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字
"""
class Solution4:
    def moreThanHalfNum(self, array):
        length = len(array)

        if length == 0:
            return 0

        result = array[0]
        times = 1
        for idx in range(1, length):
            if times == 0:
                result = array[idx]
                times = 1
            elif result == array[idx]:
                times += 1
            else:
                times -= 1

        times = 0

        for i in range(length):
            if result == array[i]:
                times += 1

        return result if (times > (length>>1)) else 0


"""
5. 连续子数组的最大和
"""
class Solution5:
    def FindMaxSumOfSubArray(self, array):
        length = len(array)

        if 0 == length:
            return 0

        maxSum = array[0]
        curSum = array[0]

        for i in range(1, length):
            if curSum <= array[i]:
                curSum = array[i]
            else:
                curSum += array[i]

            if curSum < maxSum:
                maxSum = curSum

        return maxSum


"""
6. 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个
"""
class Solution6:
    def printMinNumber(self, array):
        length = len(array)
        if length == 0:
            return ""
        compare = lambda a, b:cmp(str(a)+str(b), str(b) + str(a))
        min_string = sorted(array, cmp=compare)
        return ''.join(str(s) for s in min_string)


"""
7. 在数组中的两个数字，如果前面一个数字大于后面的数字，
则这两个数字组成一个逆序对。输入一个数组,求出这个数组中
的逆序对的总数P并将P对1000000007取模的结果输出
"""
class Solution7:
    def InversePairs(self, data):
        length = len(data)
        if not length:
            return 0
        temp = [i for i in data]

        return self.mergeSort(self, data, temp, 0, length-1)%1000000007

    def mergeSort(self, data, temp, begin, end):
        if begin >= end:
            temp[begin] = data[begin]

        mid = (begin + end)>>1

        leftCount = self.mergeSort(data, temp, begin, mid)

        rightCount = self.mergeSort(data, temp, mid+1, end)

        i = mid
        j = end
        tempIndex = end;
        count = 0
        while (i>=begin and j>mid):
            if data[i] > data[j]:
                temp[tempIndex] = data[i]
                count += j-mid
                i -= 1
            else:
                temp[tempIndex] = data[j]
                j -= 1

            tempIndex -= 1

        while i>=begin:
            temp[tempIndex] = data[i]
            tempIndex -= 1
            i -= 1

        while j>mid:
            temp[tempIndex] = data[j]
            tempIndex -= 1
            j -= 1

        return leftCount + rightCount + count


"""
8. 统计一个数字在有序数组中出现的次数
"""
class Solution8:
    def CountNumbers(self, data, k):
        return data.count(k)


"""
9. 一个整数型数组里除了两个数字之外，其他的数字都出现了两次。
找出两个只出现一次的数字要求时间复杂度是O(n), 空间复杂度是O(1)
"""
class Solution9:
    def FindNumsAppearOnce(self, data):
        length = len(data)
        if not length:
            return []
        resultExclusiveOR = 0

        # 求出数组中所有元素异或值
        for i in data:
            resultExclusiveOR ^= i

        indexBitVal = self.FirstBitIs1(resultExclusiveOR)

        num1, num2 = 0, 0
        for i in data:
            if self.BitIs1(i, indexBitVal):
                num1 ^= i
            else:
                num2 ^= i

        return num1, num2


    def FirstBitIs1(self, exclusiveOR):
        indexBit = 0

        while (exclusiveOR & 1 == 0) and (indexBit <= 32):
            exclusiveOR = exclusiveOR >> 1
            indexBit += 1

        return indexBit



    def BitIs1(self, num, indexBit):
        num = num >> indexBit

        return num & 1



"""
10. 在一个长度为n的数组里的所有数字都在0到n-1的范围内。
数组中某些数字是重复的，但不知道有几个数字是重复的。
也不知道每个数字重复几次。请找出数组中任意一个重复的数字
"""
class Solution10:
    def duplicate(self, data, duplication):
        length = len(data)
        if not length:
            return False

        # 元素小于0，或者大于下标， 异常
        for i in range(length):
            if data[i] < 0 or data[i] >= length:
                return False

        for i in range(length):
            if 1:
                while data[i] != i:
                    if data[i] == data[data[i]]:
                        duplication[0] = data[i]
                        return True
                    data[data[i]], data[i] = data[i], data[data[i]]
            else:
                index = data[i]
                if index >= length:
                    index -= length

                if data[index] >= length:
                    duplication[0] = index
                    return True

                data[index] += length
        return False

""""
11. 给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],
其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。不能使用除法
"""
class Solution13:
    def multiply(self, A):
        B = []
        if len(A) == 0:
            return B
        else:
            for i in range(len(A)):
                tmp = A[i]
                A[i] = 1
                B[i].append(reduce(lambda x,y:x*y, A))
                A[i] = tmp









