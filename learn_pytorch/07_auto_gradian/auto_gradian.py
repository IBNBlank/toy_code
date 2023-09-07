#!/usr/bin/env python3
################################################################
# Copyright 2021 HUST Control Science Innovation Base.
# All rights reserved.
# Author: Dong Zhaorui 847235539@qq.com
# Date  : 2021-12-07
################################################################

import torch

print("###############################################################\n")
# 简单示例
# y = 2 * torch.dot(x, x)
x = torch.arange(4, dtype=torch.float32, requires_grad=True)
y = 2 * torch.dot(x, x)
y.backward()
print(f"### y = 2 * torch.dot(x, x) ###")
print(f"### x.grad : ###\n{x.grad}")
print(f"### x.grad == 4 * x : ###\n{x.grad == 4 * x}\n")
# y = x.sum()
x.grad.zero_()
y = x.sum()
y.backward()
print(f"### y = x.sum() ###")
print(f"### x.grad : ###\n{x.grad}\n")

print("###############################################################\n")
# detach转化为常数
# y = (x*x).sum()
x.grad.zero_()
y = (x * x).sum()
y.backward()
print(f"### y = (x * x).sum() ###")
print(f"### x.grad : ###\n{x.grad}")
print(f"### x.grad == 2 * x : ###\n{x.grad == 2 * x}\n")
# z = u * x
x.grad.zero_()
y = x * x
# 将u作为常数
u = y.detach()
z = (u * x).sum()
z.backward()
print(f"### y = (u * x).sum() ###")
print(f"### x.grad : ###\n{x.grad}")
print(f"### x.grad == u : ###\n{x.grad == u}\n")

print("###############################################################\n")
# python控制流求导


def f(a):
    b = a * 2
    while b.norm() < 1000:
        b = b * 2
    if b.sum() > 0:
        c = b
    else:
        c = 100 * b
    return c


a = torch.randn(size=(), requires_grad=True)
d = f(a)
d.backward()
print(f"### a : ###\n{a}")
print(f"### a.grad : ###\n{a.grad}")
print(f"### a.grad == d / a : ###\n{a.grad == d / a}\n")
