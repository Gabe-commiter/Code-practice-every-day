#include "util.h"
//手写冒泡排序(带标着变量)
void bubble_sort(vector<int >& nums){
    for(int j=nums.size()-1;j>0;--j){
        bool flag = false;
        for (int i = 0; i < j; ++i) {
            if(nums[i] > nums[i+1])
            {
                swap(nums[i],nums[i+1]);
                flag = true;
            }
        }
        if(!flag)break;
    }
}
//手写选择排序
void mysel_sort(vector<int> &nums){
    for (int i = 0; i < nums.size()-1; ++i) {
        int k = i;
        for(int j = i+1;j<nums.size();++j)
        {
            if(nums[j] < nums[k])
                k = j;
        }
        if(k != i)
            swap(nums[i],nums[k]);
    }
}
//手写插入排序
void ins_sort(vector<int>& nums){
    for (int i = 1; i < nums.size(); ++i) {
        int key = nums[i];
        int j =i-1;
        for (; (j>=0) && (key < nums[j]); --j) {
            nums[j +1] =nums[j];
        }
        nums[j+1] = key;
    }
}
//手写希尔排序
void shell_sort(vector<int>&nums){
    int gap,i,j;
    int tmp;
    for (gap = nums.size() >>1;gap >0  ; gap >>= 1) {
        for(i = gap;i<nums.size();++i){
            tmp = nums[i];
            for (j = i-gap; j >=0 && nums[j] > tmp ; j-=gap) {
                nums[j+gap] = nums[j];
            }
            nums[j+gap] = tmp;
        }
    }
}
//手写快排
int partion(vector<int>&nums, int l, int r){
    int privot = nums[l];
    while (l < r){
        while ( l< r && nums[r] >= privot)
            --r;
        nums[l] = nums[r];
        while (l < r && nums[l] <= privot)
            ++l;
        nums[r] = nums[l];
    }
    return l;


}
void quick_sort(vector<int>& nums,int l ,int r){
  if(r-l < 2)return;
  int mid = partion(nums,l,r);
  quick_sort(nums,l,mid);
  quick_sort(nums,mid+1,r);
}
//手写归并
void merge_sort_recursive(vector<int>&nums,vector<int>&reg,int s, int e){
    if(s >= e) return;
    int mid = s + (e-s)/2;
    int s1 = s,e1=mid,s2=mid+1,e2=e;
    merge_sort_recursive(nums,reg,s1,e1);
    merge_sort_recursive(nums,reg,s2,e2);
    int k =s ;
    while (s1 <= e1 && s2<=e2)
        reg[k++] = nums[s1] < nums[s2] ? nums[s1++] : nums[s2++];
    while (s1 <= e1)
        reg[k++] = nums[s1++];
    while (s2 <= e2)
        reg[k++] = nums[s2++];
    for ( k = s; k <= e ; ++k) {
        nums[k] = reg[k];
    }

}
void merge_sort(vector<int>&nums){
    vector<int>reg(nums.size());
    merge_sort_recursive(nums,reg,0,nums.size()-1);
}
//手写堆排
//void swap(int *a, int *b) {
//    int temp = *b;
//    *b = *a;
//    *a = temp;
//}
void max_heapify(vector<int>&arr, int start, int end) {
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;
        if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比较
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(vector<int>&arr) {
    int len = arr.size();
    int i;
    // 初始化，i從最後一個父節點開始調整
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    // 先將第一個元素和已排好元素前一位做交換，再重新調整，直到排序完畢
    for (i = len - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}
//基数排序
list<int> lt[10];
int maxbit(vector<int>& nums,int n){
    int maxData = nums[0];
    for (int i = 1; i < n; ++i) {
        if(maxData < nums[i])
            maxData = nums[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >=p){
        maxData /= 10;
        ++d;
    }
    return d;
}
//分别取个位、十位、百位
int Getkey(int value, int k){
    int key;
    while (k>0)
    {
        key = value % 10;
        value /= 10;
        --k;
    }
    return key;
}
void Distrubute(vector<int>& arr, int n,int k){
    for (int i = 0; i < n; ++i) {
        int key = Getkey((arr)[i],k);
        lt[key].push_back(arr[i]);
    }
}
void Collect(vector<int>& arr){
    int n = 0;
    list<int>::iterator it;
    for (int i = 0; i < 10; ++i) {
        it = lt[i].begin();
        while (it != lt[i].end()){
            arr[n++] = *it;
            ++it;
        }
        lt[i].clear();
    }
}
void RadixSort(vector<int>& arr){
    int n =arr.size();
    int k =maxbit(arr,n);
    for (int i = 1; i <=k ; ++i) {
        Distrubute(arr,n,i);
        Collect(arr);
    }
}
//桶排序
#include<iterator>
#include<iostream>
#include<vector>
using namespace std;
const int BUCKET_NUM = 10;//桶的数目10个
//定义一个链表节点
struct ListNode{
    explicit ListNode(int i=0):mData(i),mNext(nullptr){}//mData默认值是0，mNext默认值为空
    ListNode* mNext;
    int mData;
};

ListNode* insert(ListNode* head,int val){
    ListNode dummyNode;//定义一个假的空节点
    ListNode *newNode = new ListNode(val);//用val值来构造一个新的节点
    ListNode *pre,*curr;
    dummyNode.mNext = head;
    pre = &dummyNode;
    curr = head;
    while(nullptr!=curr && curr->mData<=val){
        pre = curr;
        curr = curr->mNext;
    }
    newNode->mNext = curr;
    pre->mNext = newNode;
    return dummyNode.mNext;
}


ListNode* Merge(ListNode *head1,ListNode *head2){
    ListNode dummyNode;
    ListNode *dummy = &dummyNode;
    while(nullptr!=head1 && nullptr!=head2){
        if(head1->mData <= head2->mData){
            dummy->mNext = head1;
            head1 = head1->mNext;
        }else{
            dummy->mNext = head2;
            head2 = head2->mNext;
        }
        dummy = dummy->mNext;//当合并入一个新的节点后，dummy的位置也要后移
    }
    if(nullptr!=head1) dummy->mNext = head1;
    if(nullptr!=head2) dummy->mNext = head2;

    return dummyNode.mNext;
}

void BucketSort(int n,vector<int>& arr){
    vector<ListNode*> buckets(BUCKET_NUM,(ListNode*)(0));
    for(int i=0;i<n;++i){
        int index = arr[i]/BUCKET_NUM;
        ListNode *head = buckets.at(index);
        buckets.at(index) = insert(head,arr[i]);
    }
    ListNode *head = buckets.at(0);
    for(int i=1;i<BUCKET_NUM;++i){
        head = Merge(head,buckets.at(i));
    }
    for(int i=0;i<n;++i){
        arr[i] = head->mData;
        head = head->mNext;
    }
}
//计数排序
//
//int main(){
//    vector<int>nums = {63, 99, 56, 62, 20, 54, 59, 13, 86, 38};
//    //bubble_sort(nums);
//    //mysel_sort(nums);
//    //ins_sort(nums);
//    //shell_sort(nums);
//    //quick_sort(nums,0,nums.size()-1);
//    //merge_sort(nums);
//    //heap_sort(nums);
//    //RadixSort(nums);
//    //BucketSort(nums.size(),nums);
//    for(auto it : nums)
//        cout<<it<<" ";
//    cout<<endl;
//
//}
void print_arr(int *arr, int n) {
    int i;
    printf("%d", arr[0]);
    for (i = 1; i < n; i++)
        printf(" %d", arr[i]);
    printf("\n");
}

void counting_sort(int *ini_arr, int *sorted_arr, int n) {
    int *count_arr = (int *) malloc(sizeof(int) * 100);
    int i, j, k;
    for (k = 0; k < 100; k++)
        count_arr[k] = 0;
    for (i = 0; i < n; i++)
        count_arr[ini_arr[i]]++;
    for (k = 1; k < 100; k++)
        count_arr[k] += count_arr[k - 1];
    for (j = n; j > 0; j--)
        sorted_arr[--count_arr[ini_arr[j - 1]]] = ini_arr[j - 1];
    free(count_arr);
}

int main(int argc, char **argv) {
    int n = 10;
    int i;
    int *arr = (int *) malloc(sizeof(int) * n);
    int *sorted_arr = (int *) malloc(sizeof(int) * n);
    srand(time(0));
    for (i = 0; i < n; i++)
        arr[i] = rand() % 100;
    printf("ini_array: ");
    print_arr(arr, n);
    counting_sort(arr, sorted_arr, n);
    printf("sorted_array: ");
    print_arr(sorted_arr, n);
    free(arr);
    free(sorted_arr);
    return 0;
}
