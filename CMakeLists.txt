cmake_minimum_required(VERSION 4.0)
project(Composition_Lab)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Composition_Lab
        BankAccount.cpp
        BankAccount.h
        CheckingAccount.h
        main.cpp
        SavingsAccount.h
        Transaction.h)
