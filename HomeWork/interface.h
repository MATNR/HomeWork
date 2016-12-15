﻿//---------------------------------------------------------------------------
// File: interface.h
// By:   HeliSRaiN
//                                                     Подключаемый интерфейс
//---------------------------------------------------------------------------
#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H
//---------------------------------------------------------------------------
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <dos.h>
#include "packcage.h"
//---------------------------------------------------------------------------
#define SMALL_SPACE ("                     ")
#define LONG_SPACE ("                                ")
//---------------------------------------------------------------------------
const int WAIT_TIME = 5000;
const int WAIT_TIME_TO_PRINT = 250;
const int WAIT_TIME_TO_LOGO = 500;
const int WAIT_TIME_TO_HIDE = 2000;
//---------------------------------------------------------------------------
int menuRun(Text *&text);
void returnToMenu(Text *&text); //Функция, которая возвращает в начальное меню
//---------------------------------------------------------------------------
#endif 