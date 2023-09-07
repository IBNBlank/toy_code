#!/usr/bin/env python3
################################################################
# Copyright 2021 HUST Control Science Innovation Base.
# All rights reserved.
# Author: Dong Zhaorui 847235539@qq.com
# Date  : 2021-12-06
################################################################

import torch

print("###############################################################\n")
# 标量由只有一个元素的tensor表示
x = torch.tensor([3.0])
y = torch.tensor([2.0])
print(f"### x : ###\n{x}\n")
print(f"### y : ###\n{y}\n")
print(f"### x + y : ###\n{x + y}\n")
print(f"### x * y : ###\n{x * y}\n")
print(f"### x / y : ###\n{x / y}\n")
print(f"### x ** y : ###\n{x ** y}\n")

print("###############################################################\n")
# 将向量视为标量组成的列表
x = torch.arange(4)
print(f"### x : ###\n{x}\n")
# 通过tensor的索引来访问任意元素
print(f"### x[3] : ###\n{x[3]}\n")

print("###############################################################\n")
# 通过分别制定两个分量m和n来创建一个形状为m*n的矩阵
A = torch.arange(20).reshape(5, 4)
print(f"### A : ###\n{A}\n")
# 矩阵的转置
print(f"### A.T : ###\n{A.T}\n")
# 对称矩阵转置等于其自身
B = torch.tensor([[1, 2, 3], [2, 0, 4], [3, 4, 5]])
print(f"### B : ###\n{B}\n")
print(f"### B == B.T : ###\n{B == B.T}\n")

print("###############################################################\n")
# 向量是标量的推广，矩阵式向量的推广，我们可以构建具有更多轴的数据结构
X = torch.arange(24).reshape(2, 3, 4)
print(f"### X : ###\n{X}\n")

print("###############################################################\n")
# 运算
# 给定具有相同形状的任何两个tensor，任何按元素二元运算的结果都将是相同形状的tensor
A = torch.arange(20, dtype=torch.float32).reshape(5, 4)
B = A.clone()
k = 2
X = torch.arange(24).reshape(2, 3, 4)
print(f"### A or B : ###\n{A}\n")
print(f"### A + B : ###\n{A + B}\n")
# 两个矩阵的按元素乘法称为哈达玛积(Hadamard Product)
print(f"### A * B : ###\n{A * B}\n")
# 标量与tensor相加，则与每个元素都加
print(f"### k + A : ###\n{k + A}\n")
# 标量与tensor相乘，则与每个元素相乘
print(f"### k * A : ###\n{k * A}\n")
# 计算tensor所有元素的和
print(f"### X.sum() : ###\n{X.sum()}\n")
# 对tensor特定轴方向所有元素求和
A = torch.arange(40, dtype=torch.float32).reshape(2, 5, 4)
print(f"### A : ###\n{A}\n")
A_sum_axis0 = A.sum(axis=0)
print(f"### A.sum(axis=0).shape : ###\n{A_sum_axis0.shape}")
print(f"### A.sum(axis=0) : ###\n{A_sum_axis0}\n")
A_sum_axis1 = A.sum(axis=1)
print(f"### A.sum(axis=1).shape : ###\n{A_sum_axis1.shape}")
print(f"### A.sum(axis=1) : ###\n{A_sum_axis1}\n")
A_sum_axis2 = A.sum(axis=2)
print(f"### A.sum(axis=2).shape : ###\n{A_sum_axis2.shape}")
print(f"### A.sum(axis=2) : ###\n{A_sum_axis2}\n")
A_sum_axis01 = A.sum(axis=[0, 1])
print(f"### A.sum(axis=[0, 1]).shape : ###\n{A_sum_axis01.shape}")
print(f"### A.sum(axis=[0, 1]) : ###\n{A_sum_axis01}\n")
# 对tensor特定轴方向所有元素求均值
A_mean_axis0 = A.mean(axis=0)
print(f"### A.mean(axis=0).shape : ###\n{A_mean_axis0.shape}")
print(f"### A.mean(axis=0) : ###\n{A_mean_axis0}\n")
A_mean_axis1 = A.mean(axis=1)
print(f"### A.mean(axis=1).shape : ###\n{A_mean_axis1.shape}")
print(f"### A.mean(axis=1) : ###\n{A_mean_axis1}\n")
A_mean_axis2 = A.mean(axis=2)
print(f"### A.mean(axis=2).shape : ###\n{A_mean_axis2.shape}")
print(f"### A.mean(axis=2) : ###\n{A_mean_axis2}\n")
A_mean_axis01 = A.mean(axis=[0, 1])
print(f"### A.mean(axis=[0, 1]).shape : ###\n{A_mean_axis01.shape}")
print(f"### A.mean(axis=[0, 1]) : ###\n{A_mean_axis01}\n")
# 对tensor特定轴方向所有元素求和，但保持轴数不变
A_sum_keep_axis0 = A.sum(axis=0, keepdim=True)
print(f"### A.sum(axis=0, keepdim=True).shape : ###\n{A_sum_keep_axis0.shape}")
print(f"### A.sum(axis=0, keepdim=True) : ###\n{A_sum_keep_axis0}\n")
# 通过广播对A某一轴归一化
print(f"### A / A.sum(axis=0, keepdim=True) : ###\n{A / A_sum_keep_axis0}\n")
# 对tensor特定轴方向做累加求和
A_cumsum_axis1 = A.cumsum(axis=1)
print(f"### A.cumsum(axis=1).shape : ###\n{A_cumsum_axis1.shape}")
print(f"### A.cumsum(axis=1) : ###\n{A_cumsum_axis1}\n")
# 点积是相同位置的元素乘积的和
x = torch.tensor([0, 1, 2, 3], dtype=torch.float32)
y = torch.ones(4, dtype=torch.float32)
print(f"### x : ###\n{x}")
print(f"### y : ###\n{y}")
print(f"### torch.dot(x, y) : ###\n{torch.dot(x, y)}\n")
# 矩阵向量乘法
A = torch.arange(20, dtype=torch.float32).reshape(5, 4)
x = torch.tensor([0, 1, 2, 3], dtype=torch.float32)
print(f"### A.shape : ###\n{A.shape}")
print(f"### x.shape : ###\n{x.shape}")
print(f"### torch.mv(A, x) : ###\n{torch.mv(A, x)}\n")
# 矩阵矩阵乘法
A = torch.arange(20, dtype=torch.float32).reshape(5, 4)
B = torch.arange(12, dtype=torch.float32).reshape(4, 3)
print(f"### A.shape : ###\n{A.shape}")
print(f"### B.shape : ###\n{B.shape}")
print(f"### torch.mm(A, B) : ###\n{torch.mm(A, B)}\n")
# 向量范数
u = torch.tensor([3.0, -4], dtype=torch.float32)
print(f"### u : ###\n{u}")
# L2范数
print(f"### torch.norm(u) : ###\n{torch.norm(u)}")
# L1范数
print(f"### torch.abs(u).sum() : ###\n{torch.abs(u).sum()}\n")
# 矩阵范数
A = torch.arange(20, dtype=torch.float32).reshape(5, 4)
print(f"### A : ###\n{A}")
# Frobenius Norm
print(f"### torch.norm(A) : ###\n{torch.norm(A)}")
