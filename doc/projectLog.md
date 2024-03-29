<h1><center>工程开发文档</center></h1>

### 工程概述

&nbsp;&nbsp;本工程旨在创建一个演示程序，用来演示和各种算法。开发环境为 `qt5.14+MinGW_64bit`。

### 可行性分析及开发计划

#### &nbsp;&nbsp;&nbsp;&nbsp;可行性分析

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;软件使用qt所提供的绘图类绘制演示动画，并进行控制。

#### &nbsp;&nbsp;&nbsp;&nbsp;开发计划

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;使用增量开发模型，一点一点的将功能完善。

### 软件需求分析

#### &nbsp;&nbsp;&nbsp;&nbsp;功能需求

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;保证基本的演示和控制演示功能。

#### &nbsp;&nbsp;&nbsp;&nbsp;性能需求

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;程序渲染动画速度快，控制和演示的过程不能出现卡顿。

#### &nbsp;&nbsp;&nbsp;&nbsp;数据需求

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;保证基本的算法可以进行演示。

#### &nbsp;&nbsp;&nbsp;&nbsp;安全及可靠性需求

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;程序尽量不出现漏洞。

#### &nbsp;&nbsp;&nbsp;&nbsp;运行环境需求

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此程序在Windows平台编写、调试、发布。但是由于qt可以执行好，可以很方便的移植到Linux平台上。

### 软件设计

&nbsp;&nbsp;&nbsp;&nbsp;软件分为主模块、演示控制模块、演示模块、算法模块、（数据模块）。

#### &nbsp;&nbsp;&nbsp;&nbsp;主模块

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;主模块为最上层模块，负责调度其他模块和接收用户数据和指令。

#### &nbsp;&nbsp;&nbsp;&nbsp;控制模块

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本模块用来执行演示进度控制指令，操纵演示模块控制演示进度。模块采用的设计模式为命令模式。

#### &nbsp;&nbsp;&nbsp;&nbsp;演示模块

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本模块用来接收演示模块和计算模块的指令，并根据指令生成相应的画面。该模块包含许多小模块其中最主要的模块为形状模块、绘制模块、展示模块。

##### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;形状模块

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;包含各种各样的形状，这些形状将作为演示的基本形状。模块采用的设计模式为工厂方法模式。

##### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;绘制模块

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;用来接受其他模块发来的指令，并根据这些指令来绘制演示图片。该模块绘制完成后会向展示模块发送演示图片。

##### &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;展示模块

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;用来接收绘制模块发来的图像并将图像展示到窗口，以及根据用户操作对图像进行缩放和移动。

#### &nbsp;&nbsp;&nbsp;&nbsp;算法模块

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本模块用来计算和保存算法的数据以及算法的介绍，并将每一步的结果发送给演示模块。模块采用的设计模式为抽象工厂模式。

   