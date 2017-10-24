#pragma once





////////////////////////////////////////////////////////
template <class T_DataType>
int Bubble_Sort(T_DataType arr[], int size)
{
	int swapcount =0;
	bool sorted = false;
	while (sorted == false)
	{
		sorted = true;
		for (int i = 0; i < size-1; ++i)
		{

			if (arr[i] >arr[i + 1])
			{
				sorted = false;
				swap(arr[i], arr[i + 1]);
				swapcount++;
			}
		}
	}
	return swapcount;
}

////////////////////////////////////////////////////////
template <class T_DataType>
int Selection_Sort(T_DataType arr[], int n)
{
	int swapcount = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (arr[j] < arr[min]) min = j;			
		}
		swap(arr[i], arr[min]);
		swapcount++;
	}
	return swapcount;
}

////////////////////////////////////////////////////////
template <class T_DataType>
int Insertion_Sort(T_DataType arr[], int n)
{
	
	int i, key, j, swapcount =0;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
			swapcount++;
		}
		arr[j + 1] = key;
	}
	return swapcount;
}

////////////////////////////////////////////////////////
template <class T_DataType>
void merge(T_DataType arr[], int left, int middle, int right)
{
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	/* create temp arrays */
	T_DataType *ArrLeft;
	T_DataType *ArrRight;
	ArrLeft = (T_DataType*)malloc(n1 * sizeof(T_DataType));
	ArrRight = (T_DataType*)malloc(n2 * sizeof(T_DataType));

	/* Copy data to temp arrays*/
	for (i = 0; i < n1; i++)
		ArrLeft[i] = arr[left + i];
	for (j = 0; j < n2; j++)
		ArrRight[j] = arr[middle + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = left; // Initial index of merged subarray
	while (i < n1 && j < n2)
	{
		if (ArrLeft[i] <= ArrRight[j])
		{
			arr[k] = ArrLeft[i];
			i++;
		}
		else
		{
			arr[k] = ArrRight[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of ArrLeft[], if there
	are any */
	while (i < n1)
	{
		arr[k] = ArrLeft[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of ArrRight[], if there
	are any */
	while (j < n2)
	{
		arr[k] = ArrRight[j];
		j++;
		k++;
	}
	free(ArrLeft);
	free(ArrRight);
}
////////////////////////////////////////////////////////

//if you are calling this function, pass (arr, 0, size-1)
template <class T_DataType>
int Merge_Sort(T_DataType arr[], int left_index, int right_index)
{
	int swapcount = 0;
	
	if (left_index < right_index)
	{
		int m = left_index + (right_index - left_index) / 2;

		// Sort first and second halves
		Merge_Sort(arr, left_index, m);
		Merge_Sort(arr, m + 1, right_index);

		merge(arr, left_index, m, right_index);
	}
	return swapcount;
}