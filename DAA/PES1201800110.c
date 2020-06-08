//intal stands for 'int'egers of 'a'rbitrary 'l'ength
// The current implementation of intal are non-negative integers of length up to 1000 decimal digits 
// The integer is stored as a null terminated string of ASCII characters in big endian format 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

#define INTAL_MAX 1008

static void intal_slice(char *intal, char *ans, int start, int end);
static char* reverse(char* intal, int n);
static char* remove_leading_zeroes(char* intal);
static void mergeSortedHalves(char **arr,int start,int mid,int end);
static void mergeSort(char **arr,int start,int end);
static int binary_search(char **arr, int start, int end, const char* key);
static char* mod_cal(const char* intal1, const char* intal2);


// Some static helper functions used throughout the assignment 
//A detailed description of these can be found in the report.txt file 

static void intal_slice(char *intal, char *ans, int start, int end)
{
    int index = 0;
    for(int i = start; i < end; ++i)
        ans[index++] = intal[i];
    ans[index] = '\0';    
}

static char* reverse(char* intal, int n){

    char temp;
	for(int i=0;i<n/2;++i){
		temp=intal[i];
		intal[i]=intal[n-i-1];
		intal[n-i-1]=temp;
	}
   	intal[n]='\0';
	return intal;

}

static char* remove_leading_zeroes(char* intal){

    int len = strlen(intal);
    int count = 0;

    while(intal[count]=='0'){
        ++count;
    }

    if(count!=0){

        for(int i=0;i<len-count+1;++i){
            intal[i] = intal[i+count];

        }

    }

    if(count==len){
        intal[0] = '0';
        intal[1] = '\0';
    }

    return intal;

}

/*
For a possilble heap sort implementation (prolly going to go with mergesort tho)
static void swap(char** a,char** b){
    char* temp = *a;
    *a = *b;
    *b = temp;
}
*/

//A function to copy (deep?) intals ?
//Slicing functionality ?

//Static Merge function 
static void mergeSortedHalves(char **arr,int start,int mid,int end){

    int i,j,k;
    int len1 = mid-start+1;
    int len2 = end-mid;

    //creation of temp arrays to store the result 
    char **l = (char **)malloc(sizeof(char *)*len1);

    for(i=0;i<len1; ++i){
        l[i] = arr[start+i];
    }  

    char **r = (char **)malloc(sizeof(char *)*len2);

    for(j=0; j<len2; ++j){
        r[j] = arr[mid+1+j];
    }

    i=0;
    j=0;
    k=start;

    while(i<len1 && j<len2){
        if(intal_compare(l[i],r[j])==-1){
            arr[k]=l[i];
            i++;
        }

        else{
            arr[k] = r[j];
            j++;
        }

        k++;

    }

    while(i<len1){

        arr[k] = l[i];
        i++;
        k++;

    }

    while(j<len2){

        arr[k] = r[j];
        j++;
        k++;

    }

    free(l);
    free(r);

}


//MergeSort function 
static void mergeSort(char **arr,int start,int end){

    if(start<end){
        int mid = start + (end-start)/2;
        mergeSort(arr,start,mid);
        mergeSort(arr,mid+1,end);
        mergeSortedHalves(arr,start,mid,end);
    }

}

//Static binary search 
static int binary_search(char **arr, int start, int end, const char* key){
    
    if(end>=start){

        int mid = start + (end-start)/2; 

        if(intal_compare(arr[mid],key)==0){
            return mid;
        }

        else if(intal_compare(arr[mid],key)==1){
            return binary_search(arr,start,mid-1,key);
        }

        else{
            return binary_search(arr,mid+1,end,key);
        }

    }

    return -1;

}


// Returns the sum of two intals.
// The length of the sum intal is atmost the greater of the two + 1

char* intal_add(const char* intal1, const char* intal2){

    char* a = (char*)malloc(sizeof(char) * INTAL_MAX);
    char* b = (char*)malloc(sizeof(char) * INTAL_MAX);

    strcpy(a, intal1);
    strcpy(b, intal2);

    if(strcmp("0", a) == 0){
        free(a);
        return b;
    }

    if(strcmp("0", b) == 0){
        free(b);
        return a;
    }

    if(strlen(a) > strlen(b)){
        strcpy(a, intal2);
        strcpy(b, intal1);
    }
    
    int len1 = strlen(a);
    int len2 = strlen(b);
    char* result = (char*)malloc(sizeof(char) * INTAL_MAX);
    int carry = 0;
    int i;
    int sum = 0, k = 0;

    for(i = len1 - 1; i >= 0; --i){
        sum = (a[i] - '0') + b[i + len2 - len1] - '0' + carry;
        result[k++] = '0' + (sum % 10);
        carry = sum / 10;
    }

    for(i = len2 - len1 - 1; i >= 0; --i){
        sum = (b[i] - '0') + carry;
        result[k++] = '0' + (sum % 10);
        carry = sum/10;
    }

    if(carry>0){
        result[k++] = carry + '0';
    }

    result[k] = '\0';
    result = reverse(result, strlen(result));
    free(a);
    free(b);
    return result;

}


// Returns the comparison value of two intals.
// Returns 0 when both are equal.
// Returns +1 when intal1 is greater, and -1 when intal2 is greater.
int intal_compare(const char* intal1, const char* intal2){

    int len1 = strlen(intal1);
    int len2 = strlen(intal2);

    if(len1<len2){
        return -1;
    }

    else if(len1>len2){
        return 1;
    }

    else{
        int i=0; // should this be 0 ?
        while(i<len1)
        {
            if(intal1[i]>intal2[i])
            {
                return 1;
            }
            else if(intal1[i]>intal2[i]){
                return -1;
            }
            ++i;
        }

        return 0;
    }

}

// Returns the difference (obviously, nonnegative) of two intals.
char* intal_diff(const char* intal1, const char* intal2){

    /*
    const char *bigIntal;
    const char *smallIntal;

    if(intal_compare(intal1,intal2) == 1){
        bigIntal = intal1;
        smallIntal = intal2;
    }

    else{
        bigIntal = intal2;
        smallIntal = intal1;
    }

    int len1 = strlen(bigIntal);
    int len2 = strlen(smallIntal);

    int len3 = len1;
    char *intal3 = (char*)malloc(sizeof(char)*INTAL_MAX);
    intal3[len3--] = '\0';
    int diff = len1 - len2;
    int carry = 0;
    
    for(int i = len2 - 1; i >=0 ; --i){

        int result = (bigIntal[i + diff] - '0') - (smallIntal[i] - '0') - carry;
        if(result < 0){
            result += 10;
            carry = 1;
        }

        else{
            carry = 0;  
        }

        intal3[len3--] = result + '0';

    }

    for(int i = diff - 1; i >=0 ; --i){

        if(bigIntal[i] == '0' && carry){
            intal3[len3--] = '9';
        }
        else{

            intal3[len3--] = bigIntal[i] - carry;
            carry = 0;
        }
    }

    return remove_leading_zeroes(intal3); 
    */

   int res=intal_compare(intal1,intal2);
	if(res==0)
	{
		char* diff=(char*)malloc(sizeof(char)*2);
		diff[0]='0';
		diff[1]='\0';
		return diff;
	}
	else
	{
		char* a;
		char* b;
		int len1;
		int len2;
		if(res==-1)
		{
			len1=strlen(intal2);
			len2=strlen(intal1);
			a=(char*)malloc(sizeof(char)*(len1+1));
			b=(char*)malloc(sizeof(char)*(len2+1));
			strcpy(a,intal2);
			strcpy(b,intal1);
		}
		else
		{
			len1=strlen(intal1);
			len2=strlen(intal2);
			a=(char*)malloc(sizeof(char)*(len1+1));
			b=(char*)malloc(sizeof(char)*(len2+1));
			strcpy(a,intal1);
			strcpy(b,intal2);
		}
		int max_len=(len1>len2?len1:len2)+1;
		char* diff=(char*)malloc(sizeof(char)*max_len);
		int i=len1-1;
		int j=len2-1;
		int k=max_len-1;
		diff[k]='\0';
		--k;
		while(i>=0 && j>=0)
		{
			int d=a[i]-b[j];
			if(d<0)
			{
				d+=10;
				a[i-1]-=1;
			}
			diff[k]=d+'0';
			--i;
			--j;
			--k;
		}
		while(i>=0)
		{
			if(a[i]<'0')
			{
				a[i]+=10;
				a[i-1]-=1;
			}
			diff[k]=a[i];
			--i;
			--k;
		}
		int f=0;
		int count=0;
		while(diff[f]=='0')
		{
			++f;
			++count;
		}
		free(a);
		free(b);
		if(count==0)
			return diff;
		char* diff1=(char*)malloc(sizeof(char)*(max_len-count));
		for(int i=0;i<max_len-count;++i)
			diff1[i]=diff[i+count];
		free(diff);
		return diff1;
	}
    

}

// Returns the product of two intals.
// The asymptotic complexity is O(m*n) i.e if n is equal O(n^2) which can be improved by implementing the Karatsuba algorithm which seemed like overkill.

char* intal_multiply(const char* intal1, const char* intal2){

    const char *bigIntal;
    const char *smallIntal;

    if(strlen(intal1) > strlen(intal2)){
        bigIntal = intal1;
        smallIntal = intal2;
    }

    else{
        bigIntal = intal2;
        smallIntal = intal1;
    }

    int len1 = strlen(bigIntal);
    int len2 = strlen(smallIntal);

   
    char* result = (char*)malloc(sizeof(char)*INTAL_MAX);
    result[0] = '0';
    result[1] = '\0';

    for(int i=0;i<len2;++i){

        int res_len = strlen(result);
        result[res_len] = '0';
        result[res_len+1] = '\0';

        char* product = (char*)malloc(sizeof(char)*INTAL_MAX);
        product[len1+1] = '\0';
        int n = smallIntal[i]-'0';

        int carry = 0;

        for(int j=len1-1; j>=0; --j){

            int partial_product = n * (bigIntal[j]-'0') + carry;
            carry = partial_product/10;
            partial_product = partial_product%10;
            product[j+1] = partial_product + '0';

        }

        product[0] = carry + '0';
        product = remove_leading_zeroes(product);
        char* Freeable = result;
        result = intal_add(result,product);
        free(Freeable);
        free(product);

    }

    return result;
    
}


// Returns intal1 mod intal2
// The mod value should be in the range [0, intal2 - 1].
// intal2 > 1
// Implement a O(log intal1) time taking algorithm.
// O(intal1 / intal2) time taking algorithm may exceed time limit.
// O(intal1 / intal2) algorithm may repeatedly subtract intal2 from intal1.
// That will take intal1/intal2 iterations.
// You need to design a O(log intal1) time taking algorithm.
// Generate your own testcases at https://www.omnicalculator.com/math/modulo
char* intal_mod(const char* intal1, const char* intal2)
{
    if(intal2[0]=='2' && intal2[1]=='\0')
	{
		char* res=(char*)malloc(sizeof(char)*2);
		int len1=strlen(intal1);
		res[0]=((intal1[len1-1]-'0')%2)+'0';
		res[1]='\0';
		return res;
	}
	int comp=intal_compare(intal1,intal2);
	if(comp==0)
	{
		char* res=(char*)malloc(sizeof(char)*2);
		res[0]='0';
		res[1]='\0';
		return res;
	}
	else if(comp==-1)
	{
		int len=strlen(intal1);
		char* res=(char*)malloc(sizeof(char)*(len+1));
		strcpy(res,intal1);
		return res;
	}
	return mod_cal(intal1,intal2);

}

static char* mod_cal(const char* intal1, const char* intal2)
{
	int comp=intal_compare(intal1,intal2);
	if(comp==0)
	{
		char* res=(char*)malloc(sizeof(char)*2);
		res[0]='0';
		res[0]='\0';
		return res;
	}
	int len1=strlen(intal1);
	if(comp==-1)
	{
		char* res=(char*)malloc(sizeof(char)*(len1+1));
		strcpy(res,intal1);
		return res;
	}
	else
	{
		int len2=strlen(intal2);
		int d=len1-len2;
		int i=0;
		while(i<len2)
		{
			if(intal1[i]>intal2[i])
				i=len2;
			else if(intal1[i]<intal2[i])
			{
				--d;
				i=len2;
			}
			++i;
		}
		int lenc=len2+d;
		char* copy2=(char*)malloc(sizeof(char)*(lenc+1));
		strcpy(copy2,intal2);
		for(i=len2;i<lenc;++i)
		copy2[i]='0';
		copy2[lenc]='\0';
		char* diff=intal_diff(intal1,copy2);
		free(copy2);
		char* res=intal_mod(diff,intal2);
		free(diff);
		return res;
	}
}




// Returns intal1 ^ intal2.
// Let 0 ^ n = 0, where n is an intal.
// Implement a O(log n) intal multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 intal multiplications may exceed time limit
char* intal_pow(const char* intal1, unsigned int n){

    char* result = (char*)malloc(sizeof(char)*INTAL_MAX);
    strcpy(result,"1");

    if(n==0){
        return result;
    }

    
    if(intal_compare(intal1,"0") == 0){
        strcpy(result,"0");
        return result;
    }

        

        char* multiple = (char*)malloc(sizeof(char)*INTAL_MAX);
        strcpy(multiple,intal1);

        while(n>0){

            if(n&1){
                char* Freeable1 = result;
                result = intal_multiply(result,multiple);
                free(Freeable1);
            }

            if(n!=1){
                char* Freeable2 = multiple;
                multiple = intal_multiply(multiple,multiple);
                free(Freeable2);
            }

            n = n>>1;

        }

        free(multiple);
        return result;
            
}


//Returns Greatest Common Divisor of intal1 and intal2.
//Let GCD be "0" if one of intal1 and intal2 is "0".
//Use Euclid's theorem to not exceed the time limit.
char* intal_gcd(const char* intal1, const char* intal2){
 
    const char *bigIntal;
    const char *smallIntal;

    if(intal_compare(intal1,intal2) == 1){
        bigIntal = intal1;
        smallIntal = intal2;
    }

    else{
        bigIntal = intal2;
        smallIntal = intal1;
    }


        if (intal_compare(smallIntal,"0") == 0){
        char *temp = (char *)malloc(sizeof(char)*INTAL_MAX);
        strcpy(temp,bigIntal); 
        return temp; 
        }

        char *temp1 = intal_mod(smallIntal,bigIntal);
        char temp2[INTAL_MAX];
        strcpy(temp2,temp1);
        free(temp1);
        return intal_gcd(smallIntal, temp2);
    

    /*
    if(intal1[0]=='0')
	{
		int len2=strlen(intal2);
		char* res=(char*)malloc(sizeof(char)*(len2+1));
		strcpy(res,intal2);
		return res;
	}
	else if(intal2[0]=='0')
	{
		int len1=strlen(intal1);
		char* res=(char*)malloc(sizeof(char)*(len1+1));
		strcpy(res,intal1);
		return res;
	}
	int comp=intal_compare(intal1,intal2);
	char* mod;
	char* res;
	if(comp==-1)
	{
		mod=intal_mod(intal2,intal1);
		res=intal_gcd(mod,intal1);
		free(mod);
	}
	else if(comp==1)
	{
		mod=intal_mod(intal1,intal2);
		res=intal_gcd(mod,intal2);
		free(mod);
	}
	else
	{
		int len1=strlen(intal1);
		res=(char*)malloc(sizeof(char)*(len1+1));
		strcpy(res,intal1);
	}
	return res;
    */
}



// Returns nth fibonacci number.
// intal_fibonacci(0) = intal "0".
// intal_fibonacci(1) = intal "1".
char* intal_fibonacci(unsigned int n){

    char* first = (char*)malloc(sizeof(char)*INTAL_MAX);
    first[0] = '0';
    first[1] = '\0';

    char* second = (char*)malloc(sizeof(char)*INTAL_MAX);
    second[0] = '1';
    second[1] = '\0';

    if (n == 0){
        return first;
    }

    if (n == 1){
        return second;
    }
  
    for (int i=2;i<n+1; ++i){
        char* sum = intal_add(first, second);
        free(first);
        first = second;
        second = sum;
    }

    free(first);
    return second;

}


//Check if this can be altered
// Returns the factorial of n.
char* intal_factorial(unsigned int n){

    // A better idea ?
    // char *result = (char *)calloc(INTAL_MAX,sizeof(char));

    char* result = (char*)malloc(sizeof(char)*INTAL_MAX);
    strcpy(result,"1");

    char* count = (char*)malloc(sizeof(char)*INTAL_MAX);
    count[0] = '1';
    count[1] = '\0';

    for(int i=0;i<n;++i){

        char *Freeable1 = result;
        char *Freeable2 = count;
        result = intal_multiply(result,count);
        count = intal_add(count,"1");
        free(Freeable1);
        free(Freeable2);

    }    

    free(count);
    return result;
    
}


// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the returning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate intal values do not cross C(n.k).
char* intal_bincoeff(unsigned int n, unsigned int k){

    char **pascal = (char **)calloc(k+1,sizeof(char *));
    
    if(n-k < k){
        k = n-k;
    }

    for(int i=0;i<k+1;++i){
        pascal[i] = (char *)calloc(INTAL_MAX, sizeof(char));
        strcpy(pascal[i],"0");
    }
    
    pascal[0][0] = '1';
    
    for (int i=1;i<=n;++i){
    
        for (int j=i<k?i:k;j>0;--j) {

            char* Freeable = pascal[j];
            pascal[j] = intal_add(pascal[j],pascal[j-1]);
            free(Freeable);
        
        }            
    } 

    char* result = (char*)malloc(INTAL_MAX);
    strcpy(result,pascal[k]);
    
    for(int i=0;i<k+1;++i){
        free(pascal[i]);
    }

    free(pascal);
    return result;

}


// Returns the offset of the largest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_max(char **arr, int n){

    int max_offset = 0;
    char* max_intal = (char*)malloc(sizeof(char)*INTAL_MAX);
    strcpy(max_intal,arr[0]); // Alternative ways to do this ?

    for(int i=1;i<n;++i){
        if(intal_compare(arr[i],max_intal)== 1){
            max_offset = i;
            strcpy(max_intal,arr[i]);
        }
    }

    free(max_intal);
    return max_offset;

}

// Returns the offset of the smallest intal in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
int intal_min(char **arr, int n){

    int min_offset = 0;
    char* min_intal = (char*)malloc(sizeof(char)*INTAL_MAX);
    strcpy(min_intal,arr[0]); // Alternative ways to do this ?

    for(int i=1;i<n;++i){
        if(intal_compare(arr[i],min_intal)== -1){
            min_offset = i;
            strcpy(min_intal,arr[i]);
        }
    }

    free(min_intal);
    return min_offset;

}


// Returns the offset of the first occurrence of the key intal in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
int intal_search(char **arr, int n, const char* key){

    for(int i=0;i<n;++i){

        if(intal_compare(arr[i],key)==0){
            return i;
        }
    }

    return -1;

}


// Returns the offset of the first occurrence of the key intal in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.

// Dummy function call to static binsearch 
int intal_binsearch(char **arr, int n, const char* key){

    int high=n-1;
	int low=0;
	int mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		int res=intal_compare(key,arr[mid]);
		if(res==0)
		{
			--mid;
			while(mid>0 && res==0)
			{
				res=intal_compare(key,arr[mid]);
				--mid;
			}
			return (mid+1);
		}
		else if(res==1)
			low=mid+1;
		else
			high=mid-1;
	}
	return -1;
    
    /*
    return binary_search(arr,0,n-1,key);
    */
}


// Sorts the array of n intals.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.

// The algorithm chosen is a Merge sort implementation for the sort function.


//Dummy function to call merge
void intal_sort(char **arr, int n){
    mergeSort(arr,0,n-1);
}


// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25

char* coin_row_problem(char **arr, int n){

    char* coin_0 = (char*)malloc(sizeof(char)*INTAL_MAX);
    strcpy(coin_0,"0");

    char* coin_1 = (char*)malloc(sizeof(char)*INTAL_MAX);
    strcpy(coin_1,arr[0]);

    for(int i=1;i<n;++i){

        char* sum = intal_add(arr[i],coin_0);

        //finds the max of the current element and the sum of the coins taken so far.
        if(intal_compare(sum,coin_1)==1){

            //char temp = (char*)malloc(sizeof(char)*INTAL_MAX);
            char temp[INTAL_MAX];
            strcpy(temp,coin_1);
            free(coin_1);
            coin_1=(char*)malloc(sizeof(char)*INTAL_MAX);
            strcpy(coin_1,sum);
            free(coin_0);
            coin_0=(char*)malloc(sizeof(char)*INTAL_MAX);
            strcpy(coin_0,temp);

        }

        else{
            strcpy(coin_0,coin_1);          
        }

        free(sum);

    }

    return coin_1;
    
}

