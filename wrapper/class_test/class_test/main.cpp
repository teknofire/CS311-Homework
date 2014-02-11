//
//  main.cpp
//  class_test
//
//  Created by will on 2/10/14.
//  Copyright (c) 2014 will. All rights reserved.
//

#include <iostream>

# include <iostream>
template <typename T>
class Wrapper
{
    typedef T value_type;
public:
    Wrapper(const T &it);
    T val();
    
private:
    T _data;
};

template <typename T>
Wrapper<T>::Wrapper(const T &it):_data(it)
{}

template <typename T>
typename Wrapper<T>::value_type Wrapper<T>::val() {
    return _data;
}

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

