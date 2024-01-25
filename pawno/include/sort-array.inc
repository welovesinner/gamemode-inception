#if defined _sort_array_included_ 
    #endinput
#endif
#define _sort_array_included_

// ------------------------------------- //
//             Macro guards              //
// ------------------------------------- //

#define SortArr@%0\32; SortArr@
#define SortArr@count_%0\32; SortArr@count_

// ------------------------------------- //
//              Definition               //
// ------------------------------------- //

#define SortedArray:%0<%1> \
        SortArr@%0[%1], SortArr@count_%0

// ------------------------------------- //
//              Functions                //  
// ------------------------------------- //

#define SortArray_Count(%0) \
        SortArr@count_%0

/* ---------------------------------------------------------------- */
/*  SortArray_Count(array[])                                        */
/*                                                                  */
/*  Returns the count of elements from the sorted array.            */
/* ---------------------------------------------------------------- */

#define SortArray_Clear(%0) \
        SortArr@count_%0 = 0

/* ---------------------------------------------------------------- */
/*  SortArray_Clear(array[])                                        */
/*                                                                  */
/*  Clear an sorted array.                                          */
/* ---------------------------------------------------------------- */

#define SortArray_Copy(%0,%1) \
        SortArr@%0 = SortArr@%1, SortArr@count_%0 = SortArr@count_%1 

/* ---------------------------------------------------------------- */
/*  SortArray_Copy(dest[], source[])                                */
/*                                                                  */
/*  Copy an sorted array in another.                                */
/* ---------------------------------------------------------------- */

#define SortArray_Contains(%0,%1) \
        (_SortArray_FindIndex(SortArr@%0, SortArr@count_%0, %1) != -1)

/* ---------------------------------------------------------------- */
/*  SortArray_Contains(array[], value)                              */
/*                                                                  */
/*  Check if an value is in the sorted array.                       */
/*                                                                  */
/*                                                                  */
/*  Returns true if value exists, otherwise false.                  */
/* ---------------------------------------------------------------- */

#define SortArray_Insert(%0,%1) \
        _SortArray_Insert(SortArr@%0, SortArr@count_%0, %1) 

stock bool:_SortArray_Insert(array[], &count, const value, const size = sizeof array) {
    if(count == size)
        return false;

    if(!count) 
        array[0] = value;

    else if(value >= array[count - 1])
        array[count] = value;

    else {
        new i = count - 1;

        while(value < array[i] && i >= 0) 
            array[i + 1] = array[i--];
     
        array[i + 1] = value;
    }

    count ++;
    return true;
}

/* ---------------------------------------------------------------- */
/*  SortArray_Insert(array[], value)                                */
/*                                                                  */
/*  Insert an value in the sorted array.                            */
/*                                                                  */
/*                                                                  */
/*  Returns true for success, otherwise false.                      */
/* ---------------------------------------------------------------- */

#define SortArray_Remove(%0,%1) \
        _SortArray_Remove(SortArr@%0, SortArr@count_%0, %1) 

stock bool:_SortArray_Remove(array[], &count, const value) {
    new 
        values_count = count,
        value_index = _SortArray_FindIndex(array, values_count, value);

    if(value_index == -1) 
        return false;

    if(value == array[--count]) 
        return true;

    while(value_index < count) 
        array[value_index] = array[++value_index];

    return true;
}

/* ---------------------------------------------------------------- */
/*  SortArray_Remove(array[], value)                                */
/*                                                                  */
/*  Remove an value from the sorted array.                          */
/*                                                                  */
/*                                                                  */
/*  Returns true if value is removed, otherwise false if value      */
/*  don't exists.                                                   */
/* ---------------------------------------------------------------- */

#define SortArray_CountOccurences(%0,%1) \
        _SortArray_CountOccurences(SortArr@%0, SortArr@count_%0, %1) 

stock _SortArray_CountOccurences(const array[], count, const value) {
    new 
        value_index = _SortArray_FindIndex(array, count, value);

    if(value_index == -1) 
        return 0;

    new 
        pivot = value_index,
        occurences = 1;

    while(pivot && array[--pivot] == value) 
        ++occurences;
 
    pivot = value_index;

    while(pivot < count && array[++pivot] == value)
        ++occurences;

    return occurences;
}

/* ---------------------------------------------------------------- */
/*  SortArray_CountOccurences(array[], value)                       */
/*                                                                  */
/*  Count occurences for a specific element from the sorted array.  */
/*                                                                  */
/*                                                                  */
/*  Returns the count.                                              */
/* ---------------------------------------------------------------- */

// ------------------------------------- //
//          Internal Functions           //
// ------------------------------------- //

stock _SortArray_FindIndex(const array[], count, const value) {
    if(!count || !(array[0] <= value <= array[--count]))
        return -1;

    if(array[0] == value)
        return 0;

    if(value == array[count])
        return count;

    new
        left, mid;

    while(left < count) {
        mid = (left + count) / 2;

        if(array[mid] == value)
            return mid;

        if(array[mid] < value)
            left = mid + 1;

        else if(array[mid] > value)
            count = mid;
    }

    return -1;
}   

/* ---------------------------------------------------------------- */
/*  _SortArray_FindIndex(array[], value)                            */
/*                                                                  */
/*  Get the index for a specific value from the sorted array.       */
/*                                                                  */
/*                                                                  */
/*  Returns the value's index, otherwise -1.                        */
/* ---------------------------------------------------------------- */