#include <sort-array>

// ------------------------------------- //
//              Utils                    //
// ------------------------------------- //

#define _@SortArray_Print_Values(%0,%1) \
        for(new i = 0; i < SortArray_Count(%0); ++i) format(%1, sizeof %1, "%s %d", %1, SortArr@%0[i]); print(%1)

// ------------------------------------- //
//              Tests                    //
// ------------------------------------- //

_@Sort_Functions_Test() {
    new 
        SortedArray:test<10>;

    //
    //  Insert Test
    //

    //Insert some values.
    SortArray_Insert(test, 5);
    SortArray_Insert(test, 6);
    SortArray_Insert(test, 0);
    SortArray_Insert(test, 2);
    SortArray_Insert(test, 3);
    SortArray_Insert(test, 4);
    SortArray_Insert(test, 9);
    SortArray_Insert(test, 7);
    SortArray_Insert(test, 10);
    SortArray_Insert(test, 13);

    SortArray_Insert(test, 1); //Overflow.

    //Check if values are sorted and inserted successfully.
    new values[10] = {0, 2, 3, 4, 5, 6, 7, 9, 10, 13}, values_count;

    for(new i = 0; i < SortArray_Count(test); ++i) {
        if(values[i] == SortArr@test[i]) 
            ++values_count;
    }

    //Stop the test if values are not matching.
    if(values_count != 10) {
        new str[128] = "[Sorted Array Tests] Insert test failed (values are not matching). Elements:";

        _@SortArray_Print_Values(test, str);

        return 1;
    }

    //
    //  Remove Test
    //

    //Remove some values.
    SortArray_Remove(test, 5);
    SortArray_Remove(test, 10);
    SortArray_Remove(test, 0);
    SortArray_Remove(test, 13);

    //Insert a value.
    SortArray_Insert(test, 5);

    //Trying to remove non-existing values.
    SortArray_Remove(test, cellmax); 
    SortArray_Remove(test, cellmin);
    SortArray_Remove(test, 40);
    SortArray_Remove(test, 20);
    SortArray_Remove(test, -1); 

    //Insert some values.
    SortArray_Insert(test, 40);
    SortArray_Insert(test, -64);

    //Remove a value.
    SortArray_Remove(test, 4); 

    //Duplicate a value.
    SortArray_Insert(test, -64);

    //Check if values are matching successfully.
    new values_[9] = {-64, -64, 2, 3, 5, 6, 7, 9, 40};

    values_count = 0;

    for(new i = 0; i < SortArray_Count(test); ++i) {
        if(values_[i] == SortArr@test[i]) 
            ++values_count;
    }

    //Stop the test if values are not matching.
    if(values_count != 9) {
        new str[128] = "[Sorted Array Tests] Remove test failed (values are not matching). Elements:";

        _@SortArray_Print_Values(test, str);

        return 1;
    }

    //
    //  Count Occurences
    //

    //Remove some values.
    SortArray_Remove(test, 2);
    SortArray_Remove(test, 3);

    //Add occurences.
    SortArray_Insert(test, -64);
    SortArray_Insert(test, -64);

    //Remove some values.
    SortArray_Remove(test, 40);

    //Insert some values.
    SortArray_Insert(test, -60);

    if(SortArray_CountOccurences(test, -64) != 4 || SortArray_CountOccurences(test, 40) != 0 || SortArray_CountOccurences(test, 6) != 1) {
        new str[128] = "[Sorted Array Tests] Count occurences test failed. Elements:";

        _@SortArray_Print_Values(test, str);

        return 1;
    }

    //Re-make old values.
    SortArray_Remove(test, -64);
    SortArray_Remove(test, -64);
    SortArray_Remove(test, -60);

    SortArray_Insert(test, 2);
    SortArray_Insert(test, 3);
    SortArray_Insert(test, 40);

    //
    //  Copy Test
    //

    new 
        SortedArray:copy<10>;

    SortArray_Copy(copy, test);

    //Check if values are matching successfully.
    values_count = 0;

    for(new i = 0; i < SortArray_Count(copy); ++i) {
        if(values_[i] == SortArr@copy[i]) 
            ++values_count;
    }

    //Stop the test if values are not matching.
    if(values_count != 9) {
        new str[128] = "[Sorted Array Tests] Copy test failed (values are not matching). Elements:";

        _@SortArray_Print_Values(copy, str);

        return 1;
    }

    //
    //  Contains Test
    //

    if(!SortArray_Contains(test, -64) || SortArray_Contains(test, 41) || SortArray_Contains(test, cellmin) || SortArray_Contains(test, 4) || 
        !SortArray_Contains(test, 9) || SortArray_Contains(test, 0) == true || SortArray_Contains(test, 40) == false) {

        return print("[Sorted Array Tests] Contains test failed.");
    }

    //
    //  Clear Test
    //

    //Clear the sorted array.
    SortArray_Clear(test);

    //Insert some values.
    SortArray_Insert(test, 64);
    SortArray_Insert(test, 28);
    SortArray_Insert(test, 128);
    SortArray_Insert(test, 32);

    //Check if values are matching successfully.
    new values__[4] = {28, 32, 64, 128};

    values_count = 0;

    for(new i = 0; i < SortArray_Count(test); ++i) {
        if(values__[i] == SortArr@test[i]) 
            ++values_count;
    }

    //Stop the test if values are not matching.
    if(values_count != 4) {
        new str[128] = "[Sorted Array Tests] Clear test failed (values are not matching). Elements:";

        _@SortArray_Print_Values(test, str);

        return 1;
    }

    return print("[Sorted Array Tests] Tests passed (6/6).");
}