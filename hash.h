#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int numZerosNeed = 6 - (k.length()%6);
        HASH_INDEX_T convertedK [k.length() + numZerosNeed];
        if(numZerosNeed != 0){
          for(int z=0; z<numZerosNeed; z++){
            convertedK[z]=0;
          }
  
        }
        int index = 0;
        int lengthNew = k.length()+numZerosNeed;
        for(int i = numZerosNeed; i < (lengthNew); i++){
          
          convertedK[i] = letterDigitToNumber(k[index]);
          index++;
         // std::cout<< convertedK[i] << std::endl;
        }

        unsigned long long w[5] = {0,0,0,0,0};
        int startIndex = k.length()+ numZerosNeed - 6;
        int w_Index = 4;
        int numWs = (k.length() + numZerosNeed)/2;
        w[w_Index] = 0;
        //convertedK[startIndex] * 36 +  convertedK[startIndex+1];
       

        for(int i = 0; i < numWs; i++){
          for(int j = 0; j < 6; j++){
            w[w_Index] = w[w_Index] * 36 +  convertedK[(startIndex+j)];
          }
          --w_Index;
          if(startIndex != 0){
            startIndex -=6;
          }
          else{
            break;
          }
       }
        
      

        HASH_INDEX_T toReturn = rValues[0]*w[0]+ rValues[1]*w[1]+ rValues[2]*w[2]
        +rValues[3]*w[3]+rValues[4]*w[4];

        return toReturn;
        


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //std::cout<< letter << std::endl;
        int letNum = letter;
        HASH_INDEX_T conversion = letNum;
        
        //converts capitals to lowercase
        if(letNum >= 65 && letNum < 97){
          conversion = letNum + 32;
        }
        
        conversion = conversion % 97;
        if(conversion > 25){
          conversion = letNum - 22;
        }
         //std::cout<< conversion << std::endl;
        return conversion;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
