#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>


//strncmp() 用来比较两个字符串的前n个字符，区分大小写，其原型为：
//int strncmp ( const char * str1, const char * str2, size_t n );

//stricmp() 用来比较字符串，不区分大小写；区分大小写比较字符串请查看strcmp()。stricmp()原型为：
//int strcmp(char *s1, char *s2);


using namespace std;

struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };


class Solution {
public:

//    21递归实现
    ListNode* mergeTwoLists1(ListNode* l1, ListNode* l2) {
        if(l1 == NULL)
            return l2;

        if(l2 == NULL)
            return l1;

        ListNode* resHead;
        if (l1->val <= l2->val ) {
            resHead = l1;
            resHead->next = mergeTwoLists1(l1->next, l2);
        }
        else {
            resHead = l2;
            resHead->next = mergeTwoLists1(l1, l2->next);
        }

        return resHead;
    }

//    21
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);

        if(l1 == NULL)
            return l2;

        if(l2 == NULL)
            return l1;

        if(l1->val <= l2->val) {
            dummyHead->next = l1;
            l1 = l1->next;
        }
        else {
            dummyHead->next = l2;
            l2 = l2->next;
        }

        ListNode* cur = dummyHead->next;

        while (l1 != NULL && l2 != NULL) {
            if(l1->val <= l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;

        }
        cur->next = (l1 ? l1 : l2 );

        return dummyHead->next;
    }

//    83
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL)
            return NULL;

        ListNode* cur = head;

        while (cur->next != NULL ) {
            ListNode* next = cur->next;
            if(cur->val == next->val) {
                cur->next = next->next;
                delete next;
            }
            else {
                cur = cur->next;
            }
        }

        return head;
    }

//    237
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;

    }

//    203
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;

        ListNode* cur = dummyHead;
        while (cur->next != NULL) {
            if(cur->next->val == val) {
                ListNode* delNode = cur->next;
                cur->next = delNode->next;
                delete delNode;
            }
            else {
                cur = cur->next;
            }
        }

        ListNode* resHode = dummyHead->next;
        delete dummyHead;

        return resHode;
    }



//    92
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* newHead = new ListNode(0);
        newHead->next = head;

        ListNode* pre = newHead;

        for (int i = 0; i < m - 1; ++i) {
            pre = pre->next;
        }

        ListNode* cur = pre->next;

        for (int j = 0; j < n - m; ++j) {
            ListNode* next = cur->next;

            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }

        return newHead->next;


    }

//    206
    ListNode* reverseList1(ListNode* head) {

        ListNode* newhead = new ListNode(0);
        newhead->next = head;
        ListNode* pre = newhead;
        ListNode* cur = pre->next;

        while (cur != NULL && cur->next != NULL) {
            ListNode* next = cur->next;

            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }
        return newhead->next;

    }


//    206
    ListNode* reverseList(ListNode* head) {

        ListNode* pre = NULL;
        ListNode* cur = head;

        while (cur != NULL) {
            ListNode* next = cur->next;

            cur->next = pre;
            pre = cur;
            cur = next;
        }

        return pre;
    }

//    202
    bool isHappy(int n) {
        if(n == 1)
            return true;
        unordered_set<int> record;
        while (record.find(n) == record.end() ) {

            record.insert(n);

            n = squareSum(n);
            if(n == 1)
                return true;
        }

        return false;
    }

    int squareSum (int n) {

        int sum = 0, temp;
        while (n) {
            temp = n % 10;
            sum += temp * temp;
            n /= 10;
        }
        return sum;
    }



//    220
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {

    }


//    217
    bool containsDuplicate(vector<int>& nums) {

    }

//    219
    bool containsNearbyDuplicate1(vector<int>& nums, int k) {

        unordered_map<int, int> record;

        for (int i = 0; i < nums.size(); ++i) {
            if(record.find(nums[i]) != record.end()
               && (i - record[nums[i]]) <= k ) {
                return true;
            }

            record[nums[i]] = i;

        }

        return false;

    }

//    219
    bool containsNearbyDuplicate(vector<int>& nums, int k) {

        unordered_set<int> record;
        for (int i = 0; i < nums.size(); ++i) {

            if(record.find(nums[i]) != record.end() ) {
                return true;
            }

            record.insert(nums[i]);

            if(record.size() == k+1 ) {
                record.erase(nums[i-k]);
            }
        }

        return false;

    }
    
//    447
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int res = 0;

        for (int i = 0; i < points.size(); ++i) {
            
            unordered_map<int, int> record;

            for (int j = 0; j < points.size(); ++j) {

                if(i != j) {
                    record[dis(points[i], points[j])] ++;
                }
            }

            for (auto m : record) {
                if(m.second > 1) {
                    res += m.second*(m.second-1);
                }
            }
        }

        return res;

    }

    int dis(pair<int, int> pair1, pair<int, int> pair2) {
        return (pair1.first - pair2.first) ^ 2 +
                                             (pair1.second - pair2.second) ^ 2;
    }

//    49
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, unordered_multiset<string>> record;

        for (string s : strs) {
            string t = s;
            sort(t.begin(), t.end());
            record[t].insert(s);
        }

        vector<vector<string>> res;
        for (auto m : record) {
            vector<string> temp(m.second.begin(), m.second.end());
            res.push_back(temp);
        }

        return res;

    }

//    454
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int > record;
        int res = 0;

        for (int i = 0; i < A.size(); ++i) {


            for (int j = 0; j < B.size(); ++j) {

                record[A[i] + B[j]] ++;
            }
        }

        for (int k = 0; k < C.size(); ++k) {

            for (int i = 0; i < D.size(); ++i) {

                int target = 0 - C[k] - D[i];
                if(record.find(target) != record.end() ) {
                    res += record[target];
                }
            }
        }

        return res;
    }

//    16
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0;
        sort(nums.begin(), nums.end());
        int minGap = INT_MAX;

        for (int i = 0; i < nums.size(); ++i) {

            int front = i + 1;
            int back = static_cast<int>(nums.size() - 1);

            while ( front < back ) {

                int sum = nums[i] + nums[front] + nums[back];
                int gap = abs(sum - target);

                if(gap < minGap) {
                    res = sum;
                    minGap = gap;
                }

                if(sum < target) front ++;
                else back --;
            }
        }

        return res;
    }

//    18
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); ++i) {
            if(nums[i] == nums[i-1] && i > 0) continue;
            for (int j = i + 1; j < nums.size(); ++j) {
                if(nums[j] == nums[j-1] && j > i+1) continue;

                int front = j + 1;
                int back = static_cast<int>(nums.size() - 1);

                while (front < back) {
                    int sum = nums[i] + nums[j] + nums[front] + nums[back];
                    if (sum < target) {
                        front ++;
                        while (front < back && nums[front] == nums[front-1])
                            front ++;

                    }
                    else if (sum > target) {
                        back --;
                        while (front < back && nums[back] == nums[back+1])
                            back --;

                    }
                    else {
                        vector<int> temp(4, 0);
                        temp[0] = nums[i];
                        temp[1] = nums[j];
                        temp[2] = nums[front];
                        temp[3] = nums[back];
                        res.push_back(temp);
                        front++, back--;
                        while (front < back && nums[front] == nums[front-1])
                            front ++;

                        while (front < back && nums[back] == nums[back+1])
                            back --;
                    }
                }
            }
        }

        return res;
    }



//    15
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); ++i) {

            int target = -nums[i];
            int front = i + 1;
            int back = static_cast<int>(nums.size() - 1);

            while (front < back) {
                if(front < back  && nums[front] + nums[back] < target) {
                    front ++;
                    while (front < back && nums[front] == nums[front-1])
                        front++;
                }
                else if(front < back && nums[front] + nums[back] > target) {
                    back --;
                    while (front < back && nums[back] == nums[back+1])
                        back --;
                }
                else {
                    vector<int> temp(3, 0);
                    temp[0] = nums[i];
                    temp[1] = nums[front];
                    temp[2] = nums[back];
                    res.push_back(temp);

                    while (front < back && nums[front] == temp[1]) front ++;
                    while (front < back && nums[back] == temp[2]) back --;

                }
            }
            while (nums[i+1] == nums[i] && i+1 < nums.size() ) i++;
        }

        return res;


    }

//    1查找表问题
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;

        unordered_map<int, int > record;


        for (int i = 0; i < nums.size(); ++i) {

            int another = target - nums[i];

            if( record.find(another) != record.end() ) {
                res[0] = record[nums[i]];
                res[1] = i;
                return res;
            }

            record[nums[i] ] = i;
        }


    }

//    350贪心算法
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end() );
        sort(nums2.begin(), nums2.end() );
        vector<int> res;

        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size() ) {
            if(nums1[i] == nums2[j] ) {
                res.push_back(nums1[i]);
                i++, j++;
            }
            else if (nums1[i] < nums2[j] ) {
                i++;
            }
            else {
                j++;
            }
        }

        return res;
    }

//    349
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> record;

        for (int i = 0; i < nums1.size(); ++i) {
            record.insert(nums1[i]);
        }

        set<int> resSet;
        for (int j = 0; j < nums2.size(); ++j) {
//            如果find不到，指针跳转到record的尾部
            if(record.find(nums2[j]) != record.end() ) {
                resSet.insert(nums2[j]);
            }
        }

        vector<int> res;
        for (auto iter = resSet.begin(); iter != resSet.end(); iter++) {
            res.push_back(*iter);
        }

        return res;
    }

//    76
    string minWindow(string s, string t) {

    }

//    438
    vector<int> findAnagrams(string s, string p) {
        int sl = static_cast<int>(s.size());
        int pl = static_cast<int>(p.size());
        vector<int> res;

        vector<int> sf(256, 0), pf(256, 0);

        for (int i = 0; i < pl; ++i) {
            pf[p[i]] ++;
            sf[s[i]] ++;
        }

        if(sf == pf )
            res.push_back(0);

        int l = 0, r = pl-1;
        while (l < sl) {
            if(r+1 < sl)
                sf[s[++r]] ++;
            sf[s[l++]] --;

            if(sf == pf)
                res.push_back(l);

        }

        return res;
    }

//    3
    int lengthOfLongestSubstring(string s) {
        int n = static_cast<int>(s.size());

        int freq[256] = {0};
        int l = 0, r = -1;
        int res = 0;

        while (l < n) {
            if(r+1 < n && freq[s[r+1]] == 0 ) {
                r++;
                freq[s[r]] ++;
            }
            else {
                freq[s[l]] --;
                l++;
            }

            res = max(res, r-l+1);
        }

        return res;
    }

//    209滑动窗口
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        int l = 0, r = -1;
        int res = n+1;
        int sum = 0;

        if (n == 0)
            return 0;

        while (l <= n-1) {
            if (sum < s && r < n-1 ) {
                sum += nums[ ++r];
            }
            else {
                if (l < n)
                    sum -= nums[ l++];
            }

            if( sum >= s) {
                res = min(res, r-l+1);
            }
        }

        if( res == n+1)
            return 0;

        return res;


    }



//    11对撞指针
    int maxArea1(vector<int>& height) {
        int n = static_cast<int>(height.size());

        int l = 0, r = n-1;
        int res = 0;

        while (l < r) {
            res = max(res, (r-l)*min(height[l], height[r]));

            if( height[l] < height[r] ) {
                l++;
            }
            else {
                r--;
            }
        }

        return res;
    }



//    11暴力解法
    int maxArea(vector<int>& height) {
        int n = static_cast<int>(height.size());
//        i[1, n]从1开始

        int res = 0;

        for (int i = 1; i < n; ++i) {

            for (int j = i+1; j <= n ; ++j) {

                res = max(res, (j-i)*min(height[i-1], height[j-1]));
            }
        }

        return res;
    }

//    345
    string reverseVowels(string s) {
        int n = static_cast<int>(s.size());

        int l = 0, r = n-1;

        while (l < r) {
            while (!isVowel(s[l]) && l < r) l++;
            while (!isVowel(s[r]) && l < r) r--;

            if(l < r) {
                swap(s[l], s[r]);
                l++, r--;
            }
        }

        return s;
    }

    bool isVowel(char c) {
        return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'a' ||
            c=='e' ||c=='i' ||c=='o' ||c=='u';

    }

//    541
    string reverseStr(string s, int k) {
        int n = static_cast<int>(s.size());

        for (int left = 0; left < n; left += 2*k) {

//            i:反转左边界， j：反转右边界
            for (int i = left, j = min(left+k-1, n-1); i < j;
                    i++, j--) {
                swap(s[i], s[j]);
            }
        }

        return s;
    }

//    344
    string reverseString(string s) {
        int n = static_cast<int>(s.size());

        int index1 = 0;
        int index2 = n-1;

        while (index1 < index2 ) {
            swap(s[index1], s[index2] );
            index1++, index2--;
        }

        return s;

    }

//    125 空字符串一般看作字符串，大小写问题？
    bool isPalindrome(string s) {
        int n = static_cast<int>(s.size());

        int index1 = 0, index2 = n-1;

        while (index1 < index2) {
//             isalnum()：判断字符是否是字母或数字；
            while (isalnum(s[index1]) == 0 && index1 < index2 ) {
                index1 ++;
            }

            while (isalnum(s[index2]) == 0 && index1 < index2 ) {
                index2 --;
            }

            if(tolower(s[index1]) != tolower(s[index2]) ) {
                return false;
            }

            index1++, index2--;
        }

        return true;


    }



//    167对撞指针方法求解: o(n)时间复杂度
//index1 = 0  index2 = n-1 向中间前进
    vector<int> twoSum1(vector<int>& numbers, int target) {
        int n = static_cast<int>(numbers.size());
        vector<int> res(2, 0);

        int index1 = 0, index2 = n-1;

//        数字不能重复使用；index1 != index2
        while (index1 < index2 ) {
            if(numbers[index1] + numbers[index2] == target) {
                res[0] = index1+1;
                res[1] = index2+1;
                return res;
            }
            else if(numbers[index1] + numbers[index2] < target) {
                index1 ++;
            }
            else if(numbers[index1] + numbers[index2] > target) {
                index2 --;
            }
        }
    }


    //167
//    使用遍历+二分搜索的方法:O(nlogn)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = static_cast<int>(numbers.size());
        vector<int> res(2, 0);

        for (int i = 0; i < n; ++i) {
            int another = target - numbers[i];

//            二分搜索[i+1, n-1];
            int l = i+1, r = n-1;
            while (l <= r) {
                int mid = (r-l)/2 + l;

                if(another == numbers[mid] ) {
                    res[0] = i+1;
                    res[1] = mid+1;
                    return res;
                }
                else if(another > numbers[mid] ) {
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
        }
    }

//    三路排序使用
    void sortColors2(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        int index1 = -1, index2 = n;
        int i = 0;
        while (i < index2 ) {
            if (nums[i] == 0 ) {
                index1 ++;
                swap(nums[i], nums[index1]);
                i ++;
            }
            else if(nums[i] == 1) {
                i ++;
            }
            else if( nums[i] == 2) {
                index2 --;
                swap(nums[i], nums[index2]);
            }

        }
    }

//    基数排序使用
    void sortColors1(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        vector<int> count(3, 0);
        for (int i = 0; i < n; ++i) {
            count[ nums[i] ] ++;
        }

        int index = 0;
        for (int j = 0; j < count[0]; ++j) {
            nums[index] = 0;
            index ++;
        }

        for (int k = 0; k < count[1]; ++k) {
            nums[index] = 1;
            index ++;
        }

        for (int l = 0; l < count[2]; ++l) {
            nums[index] = 2;
            index ++;
        }
    }

    void sortColors(vector<int>& nums) {
//        基数排序
        int n = static_cast<int>(nums.size());

        vector<int> count(3, 0);
        for (int i = 0; i < n; ++i) {
            count[ nums[i] ] ++;
        }

        int index = 0;
//      改进版本
        for (int m = 0; m < count.size(); ++m) {
            for (int i = 0; i < count[m]; ++i) {
                nums[index] = m;
                index ++;
            }
        }


    }

    int removeDuplicates1(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        //k是已经无重复数组的最后元素索引
        int k = -1;
        for (int i = 0; i < n; ++i) {

//            处理一下开始元素
            if(i < 1 || nums[i] != nums[k] ) {
                k++;
                swap(nums[ k ], nums[i]);

//                第一次交换完成后检查是否可以进行第二次重复元素交换
                if( nums[i+1] == nums[k] ) {
                    i ++;
                    k ++;

                    swap(nums[i], nums[k]);
                }
            }
        }

        for (int j = k+1; j < n; ++j) {
            nums.pop_back();
        }

        return static_cast<int>(nums.size());
    }

    int removeDuplicates(vector<int>& nums) {

        int n = static_cast<int>(nums.size());

        //k是已经无重复数组的最后元素索引
        int k = 0;
        for (int i = 1; i < n; ++i) {
            if( nums[i] != nums[k] ) {
                k++;
                swap(nums[ k ], nums[i]);
            }
        }

        for (int j = k+1; j < n; ++j) {
            nums.pop_back();
        }

        return static_cast<int>(nums.size());
    }

    int removeElement(vector<int>& nums, int val) {
        int n = static_cast<int>(nums.size());
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if(nums[i] != val ) {
                swap(nums[i], nums[k]);
                k++;
            }
        }

        for (int j = k; j < n; ++j) {
            nums.pop_back();
        }

        return static_cast<int>(nums.size());
    }

    void moveZeroes2(vector<int>& nums) {

        int k = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if(nums[i] ) {
                nums[k] = nums[i];
                k++;
            }
        }

        for (int j = k; j < nums.size(); ++j) {
            nums[j] = 0;
        }
    }

//    时间复杂度O(n)
//      空间复杂度O(1)
    void moveZeroes1(vector<int>& nums) {

        int k = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if(nums[i] ) {
                //nums[k] = nums[i];
                //如果数组中基本没有0(i == k)的话怎么优化？
                if( i != k)
                    swap(nums[i], nums[k ++]);
                else
                    k++;
            }
        }


    }


//        使用辅助空间
    void moveZeroes(vector<int>& nums) {

        vector<int> newList;

        for (int i = 0; i < nums.size(); ++i) {
            if( nums[i] ) {
                newList.push_back(nums[i]);
            }
        }

        for (int j = 0; j < newList.size(); ++j) {
            nums[j] = newList[j];
        }

        for (int l = static_cast<int>(newList.size()); l < nums.size(); ++l) {
            nums[l] = 0;
        }
    }

// 对于一个有序循环数组arr，返回arr中的最小值。
// 有序循环数组是指，有序数组左边任意长度的部分放到右边去，右边的部分拿到左边来。
// 比如数组[1,2,3,3,4]，是有序循环数组，[4,1,2,3,3]也是。
    int getMin(vector<int> arr, int n) {
        //最小值index
        //arr[l] >= arr[r]
        //arr[mid] < arr[r] ? r = mid - 1

        if(n == 0) {
            return -1;
        }

        int l = 0, r = n - 1;


//        此处一旦l <= r， 必须考虑循环终止问题
        while ( l < r ) {

            if(r - l == 1)
                break;

            if(arr[l] < arr[r])
                return arr[l];

            int mid = ( r - l)/2 + l;

            if(arr[mid] < arr[r] ) {
                r = mid;
                continue;
            }
            else if( arr[mid] > arr[l]) {
                l = mid;
                continue;
            }

//            if arr[mid] >=  arr[r]
//            arr[mid] <= arr[l]
//            可得到arr[mid ] == arr[r] == arr[l]
//            此时需要使用遍历方法解决[l, r]

            while (l < r) {
                if( arr[l] == arr[mid]) {
                    l ++;
                    continue;
                }
                else if (arr[l] < arr[mid]) {
                    return arr[l];
                }
                else if (arr[l] > arr[mid]){
                    r = mid;
                    break;
                }
            }
        }

        return min(arr[l], arr[r]);


    }

//    二分搜索直接查找最左边的num
//    1,2,2,3,3,3,3,4,5,6 num = 3
    int findPos2(vector<int> arr, int n, int num) {
        if( n <= 0)
            return -1;

        int l = 0, r = n-1;
        int res = -1;

        while (l <= r) {
            int mid = (r - l)/2 + l;

//            当相等的时候，把r = mid继续二分搜索
            if(num == arr[mid]) {
                r = mid - 1;
                res = mid;
            }
            else if(num < arr[mid]) {
                r = mid - 1;
            }
            else {
                l = mid + 1;
            }
        }
//        此处需要判断一下此处是否为num
//        if(arr[r] != num)
//            return -1;

        return res;


    }
//对于一个有序数组arr，再给定一个整数num，请在arr中找到num这个数出现的最左边的位置
// 给定一个数组arr及它的大小n，同时给定num。请返回所求位置。若该元素在数组中未出现，请返回-1。
    int findPos(vector<int> arr, int n, int num) {
        if(n == 0) {
            return -1;
        }

        //出现在最左边arr[i] > arr[i-1]
        int l = 0, r = n-1;
        int res = -1;
        while (l <= r) {
            int mid = ( r - l )/2 + l;

            if( arr[mid] == num ) {
                res = mid;
            }
            else if ( num < arr[mid]) {
                r = mid - 1;
            }
            else if(num > arr[mid] ) {
                l = mid + 1;
            }
        }

        if( res == 0 || res == -1)
            return res;
//      二分查找到num之后向左遍历，这个方法比较麻烦
        while (arr[res] == arr[res-1]) {
            res --;
            if(res == 0)
                break;
        }

        return res;

    }


//局部最小值
// n == 0 arr[o] is min return 0
// 如果arr[N-1]<arr[N-2]，那么arr[N-1]是局部最小；return n-1
// 如果0<i<N-1，既有arr[i]<arr[i-1]又有arr[i]<arr[i+1]，那么arr[i]是局部最小 return i
    int getLessIndex(vector<int> arr) {
        int n = static_cast<int>(arr.size());
        if(n <= 0)
            return -1;

        if(n == 1 || arr[0] < arr[1]) {
            return 0;
        }
        else if(arr[n-1] < arr[n-2]) {
            return n - 1;
        }
        else {
//        找到最小值，最小值必然成立[1, n-2]
            int l = 1, r = n-2;
            while (l <= r) {
                int mid = (r - l)/2 + l;
                if(arr[mid] < arr[mid-1] && arr[mid] < arr[mid+1]) {
                    return mid;
                }
                else if(arr[mid] > arr[mid-1]) {
                    r = mid - 1;
                }
                else if(arr[mid] > arr[mid+1]){
                    l = mid + 1;
                }
            }
        }

        return -1;

    }


//二分搜索
    int binarySearch(vector<int> arr, int target) {
        long n = arr.size();

        long l = 0, r = n-1;

        while (l <= r) {
//        每次开始二分搜索之前定义mid
            long mid = (r - l)/2 + l;

            if(arr[mid] == target) {
                return static_cast<int>(mid);
            }
            else if(target > arr[mid]) {
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }

        return -1;
    }

    int main() {
        std::cout << "Hello, World!" << std::endl;
        return 0;
    }
};

