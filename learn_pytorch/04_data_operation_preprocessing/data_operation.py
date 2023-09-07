#!/usr/bin/env python3
################################################################
# Copyright 2021 HUST Control Science Innovation Base.
# All rights reserved.
# Author: Dong Zhaorui 847235539@qq.com
# Date  : 2021-12-06
################################################################

import torch

print("###############################################################\n")
# tensor表示一个数组，这个数组可能有多个维度
x = torch.arange(12)
print(f"### torch.arange(12) : ###\n{x}\n")

# 通过tensor的shape属性来访问tensor的形状和元素总数
print(f"### x.shape : ###\n{x.shape}\n")
print(f"### x.numel() : ###\n{x.numel()}\n")

# 通过reshape可以改变tensor的形状而不改变元素数量和元素值
X = x.reshape(3, 4)
print(f"### x.reshape(3, 4) : ###\n{X}\n")

print("###############################################################\n")
# 使用全0、全1或者随机的数字创建tensor
zero_tensor = torch.zeros((2, 3, 4))
print(f"### torch.zeros((2, 3, 4) : ###\n{zero_tensor}\n")
one_tensor = torch.ones((2, 3, 4))
print(f"### torch.ones((2, 3, 4)) : ###\n{one_tensor}\n")
random_tensor = torch.rand((2, 3, 4))
print(f"### torch.rand((2, 3, 4)) : ###\n{random_tensor}\n")

# 使用python的list创建tensor
list_tensor = torch.tensor([[2, 1, 4, 3], [1, 2, 3, 4], [4, 3, 2, 1]])
print(f"### torch.tensor(python_list) : ###\n{list_tensor}\n")
print(f"### list_tensor.shape : ###\n{list_tensor.shape}\n")

print("###############################################################\n")
# 标准算数运算
x = torch.tensor([1.0, 2, 4, 8])
print(f"### x : ###\n{x}\n")
y = torch.tensor([2, 2, 2, 2])
print(f"### y : ###\n{y}\n")
print(f"### x + y : ###\n{x + y}\n")
print(f"### x - y : ###\n{x - y}\n")
print(f"### x * y : ###\n{x * y}\n")
print(f"### x / y : ###\n{x / y}\n")
print(f"### x ** y (求幂运算) : ###\n{x ** y}\n")
print(f"### torch.exp(x) : ###\n{torch.exp(x)}\n")

print("###############################################################\n")
# tensor连结
X = torch.arange(12, dtype=torch.float32).reshape((3, 4))
print(f"### X : ###\n{X}\n")
Y = torch.tensor([[2.0, 1, 4, 3], [1, 2, 3, 4], [4, 3, 2, 1]])
print(f"### Y : ###\n{Y}\n")
print(f"### torch.cat((X, Y), dim=0) : ###\n{torch.cat((X, Y), dim=0)}\n")
print(f"### torch.cat((X, Y), dim=1) : ###\n{torch.cat((X, Y), dim=1)}\n")

print("###############################################################\n")
# 通过逻辑运算符构成二元tensor
print(f"### X == Y : ###\n{X == Y}\n")

print("###############################################################\n")
# 通过广播机制(broadcasting mechanism)按元素操作形状不同的tensor
a = torch.arange(3).reshape((3, 1))
print(f"### a : ###\n{a}\n")
b = torch.arange(2).reshape((1, 2))
print(f"### b : ###\n{b}\n")
print(f"### a + b : ###\n{a + b}\n")

print("###############################################################\n")
# 元素的访问
print(f"### X : ###\n{X}\n")
# 访问第一个元素
print(f"### X[0] : ###\n{X[0]}\n")
# 访问最后一个元素
print(f"### X[-1] : ###\n{X[-1]}\n")
# 访问第二个和第三个元素
print(f"### X[1:3] : ###\n{X[1:3]}\n")
# 访问第二个到末尾的元素
print(f"### X[1:] : ###\n{X[1:]}\n")
# 访问开头到倒数第二个的元素
print(f"### X[:-1] : ###\n{X[:-1]}\n")

print("###############################################################\n")
# 内存管理
# 普通操作
before = id(Y)
Y = Y + X
after = id(Y)
print(f"### 普通操作前后内存位置 : ###\nbefore : {before}\nafter : {after}")
print(f"### 是否为原地址 : ###\nbefore : {before == after}\n")
# 原地操作
before = id(Y)
Y[:] = X + Y
after = id(Y)
print(f"### Y[:] = X + Y 操作前后内存位置 : ###\nbefore : {before}\nafter : {after}")
print(f"### 是否为原地址 : ###\nbefore : {before == after}\n")
before = id(Y)
Y += X
after = id(Y)
print(f"### Y += X 操作前后内存位置 : ###\nbefore : {before}\nafter : {after}")
print(f"### 是否为原地址 : ###\nbefore : {before == after}\n")

print("###############################################################\n")
# 转化
# Numpy与tensor
A = X.numpy()
B = torch.tensor(A)
print(f"### type(pytorch_tensor.numpy()) : ###\n{type(A)}\n")
print(f"### type(torch.tensor(numpy_array)) : ###\n{type(B)}\n")
# 将大小为1的张量转化为Python标量
a = torch.tensor([3.5])
print(f"### a : ###\n{a}\n")
print(f"### a.item() : ###\n{a.item()}\n")
print(f"### float(a) : ###\n{float(a)}\n")
print(f"### int(a) : ###\n{int(a)}\n")
