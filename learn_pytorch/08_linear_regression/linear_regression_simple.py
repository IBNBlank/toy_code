#!/usr/bin/env python3
################################################################
# Copyright 2021 HUST Control Science Innovation Base.
# All rights reserved.
# Author: Dong Zhaorui 847235539@qq.com
# Date  : 2021-12-08
################################################################


import numpy as np
import torch
from torch.utils import data
from d2l import torch as d2l
from torch import nn


# 调用pytorch现有的api读取数据
def load_array(data_arrays, batch_size, is_train=True):
    data_set = data.TensorDataset(*data_arrays)
    return data.DataLoader(data_set, batch_size, shuffle=is_train)


def main():
    # 构造人造数据集
    true_w = torch.tensor([2, -3.4])
    true_b = 4.2
    features, labels = d2l.synthetic_data(true_w, true_b, 10_000)

    # 定义初始化模型及参数
    net = nn.Sequential(nn.Linear(2, 1))
    net[0].weight.data.normal_(0, 0.01)
    net[0].bias.data.fill_(0)

    # 定义损失函数
    loss = nn.MSELoss()

    # 定义训练器
    trainer = torch.optim.SGD(net.parameters(), lr=0.03)

    # 定义迭代器
    batch_size = 100
    data_iter = load_array((features, labels), batch_size)

    # 训练
    num_epochs = 3
    for epoch in range(num_epochs):
        for X, y in data_iter:
            l = loss(net(X), y)
            trainer.zero_grad()
            l.backward()
            trainer.step()
        l = loss(net(features), labels)
        print(f'epoch : {epoch + 1} , loss : {l:f}')

    # 比较误差
    print(f'w的估计误差 : {true_w - net[0].weight.data.reshape(true_w.shape)}')
    print(f'b的估计误差 : {true_b - net[0].bias.data}')


if __name__ == '__main__':
    main()
