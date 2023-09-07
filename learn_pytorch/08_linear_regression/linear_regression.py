#!/usr/bin/env python3
################################################################
# Copyright 2021 HUST Control Science Innovation Base.
# All rights reserved.
# Author: Dong Zhaorui 847235539@qq.com
# Date  : 2021-12-08
################################################################

import random
import torch
from d2l import torch as d2l


# 构造人造数据集
# w = [2, -3.4]T
# b = 4.2
# e为噪声
# y = Xw + b + e
def synthetic_data(w, b, num_examples, plot=False):
    X = torch.normal(0, 1, (num_examples, len(w)))
    y = torch.matmul(X, w) + b
    y += torch.normal(0, 0.01, y.shape)
    y = y.reshape((-1, 1))

    if plot:
        d2l.set_figsize()
        d2l.plt.scatter(X[:, 1].detach().numpy(), y.detach().numpy(), 1)
        d2l.plt.show()

    return X, y


# 定义一个data_iter()函数
# 该函数接收batch_size，features，labels作为输入
# 生成大小为batch_size的小批量
def data_iter(batch_size, features, labels):
    num_examples = len(features)
    indices = list(range(num_examples))
    # 这些样本随机读取，没有特定顺序
    random.shuffle(indices)
    for i in range(0, num_examples, batch_size):
        batch_indices = torch.tensor(
            indices[i: min(i + batch_size, num_examples)])
        yield features[batch_indices], labels[batch_indices]


# 定义模型：线性回归模型
def linreg(X, w, b):
    return torch.matmul(X, w) + b


# 定义损失函数：均方损失函数
def squared_loss(y_hat, y):
    return (y_hat - y.reshape(y_hat.shape))**2/2


# 定义优化算法：小批量随机梯度下降
def sgd(params, lr, batch_size):
    with torch.no_grad():
        for param in params:
            param -= lr * param.grad / batch_size
            param.grad.zero_()


def main():
    # 构造人造数据集
    true_w = torch.tensor([2, -3.4])
    true_b = 4.2
    features, labels = synthetic_data(true_w, true_b, 10_000)

    # 定义初始化模型及参数
    net = linreg
    w = torch.normal(0, 0.01, size=(2, 1), requires_grad=True)
    b = torch.zeros(1, requires_grad=True)

    # 定义损失函数
    loss = squared_loss

    # 定义参数
    batch_size = 100
    lr = 0.03
    num_epochs = 3

    # 训练
    for epoch in range(num_epochs):
        for X, y in data_iter(batch_size, features, labels):
            l = loss(net(X, w, b), y)
            # l的形状是(batch_size, 1)，而不是一个标量
            l.sum().backward()
            sgd([w, b], lr, batch_size)
        with torch.no_grad():
            train_l = loss(net(features, w, b), labels)
            print(f'epoch : {epoch + 1} , loss : {float(train_l.mean()):f}')

    # 比较误差
    print(f'w的估计误差 : {true_w - w.reshape(true_w.shape)}')
    print(f'b的估计误差 : {true_b - b}')


if __name__ == '__main__':
    main()
