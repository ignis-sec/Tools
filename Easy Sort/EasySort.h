#pragma once






template <class T_DataType>
int Bubble_Sort(T_DataType **arr, int size)
{
	int iSwap=0;
	bool sorted = false;

	for (int i = 0; i < size && !sorted; ++i)
	{
		sorted = true;
		if (arr[i] >arr[i + 1])
		{
			sorted = false;
			swap(arr[i], arr[i + 1]);
			iSwap++;
		}	
	}
	return iSwap;
}

template <class T_DataType>
int Selection_Sort(T_DataType **arr, int n)
{
	int iSwap = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (arr[j] < arr[min]) min = j;			
		}
		swap(arr[i], arr[min]);
		iSwap++;
	}
	return iSwap;
}
/*
template <class T_DataType>
void swap(T_DataType a, T_DataType b)
{
	T_DataType temp;
	temp  =    a;
	a     =    b;
	b     =    temp;
	return;
}*/