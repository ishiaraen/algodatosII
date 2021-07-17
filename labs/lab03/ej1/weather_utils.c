#include "array_helpers.h"
#include "weather.h"

int temp_min_his(WeatherTable array){
    int temp_min = array[0u][january][0u]._min_temp;
    for(unsigned int year = 0u; year < YEARS; ++year){
        for(t_month month = january; month <= december; ++month) {
            for(unsigned int day = 0u; day < DAYS; ++day) {
                if(array[year][month][day] <= temp_min){
                    temp_min = a[year][month][day];
                }
            }
	    }
	}
	return temp_min;
}

void max_temp_anual(WeatherTable array,int output[YEARS]){
    int temp_max;
    for(unsigned int year = 0u; year < YEARS; ++year){
        temp_max = array[year][january][0u]._max_temp;
        for(t_month month = january; month <= december; ++month) {
            for(unsigned int day = 0u; day < DAYS; ++day) {
                if(array[year][month][day] <= temp_max){
                    temp_max = a[year][month][day];
                 }
            } 
        }
    output[year] = temp_max;
    }
}
