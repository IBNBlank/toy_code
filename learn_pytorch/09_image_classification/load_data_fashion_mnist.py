#!/usr/bin/env python3
# -*- coding: utf-8 -*-
################################################################
# Copyright 2021 HUST Control Science Innovation Base.
# All rights reserved.
# Author: Dong Zhaorui 847235539@qq.com
# Date  : 2021-12-11
################################################################

import torch
import torchvision
from torch.utils import data
from torchvision import transforms


def get_dataloader_workers():
    # 使⽤4个进程来读取数据。
    return 4


def load_data_fashion_mnist(batch_size, resize=None):
    # 通过pytorch自带函数下载Fashion-MNIST数据集，然后将其加载到内存中。
    trans = [transforms.ToTensor()]
    if resize:
        trans.insert(0, transforms.Resize(resize))
    trans = transforms.Compose(trans)
    mnist_train = torchvision.datasets.FashionMNIST(root="../data",
                                                    train=True,
                                                    transform=trans,
                                                    download=True)
    mnist_test = torchvision.datasets.FashionMNIST(root="../data",
                                                   train=False,
                                                   transform=trans,
                                                   download=True)
    return (data.DataLoader(mnist_train,
                            batch_size,
                            shuffle=True,
                            num_workers=get_dataloader_workers()),
            data.DataLoader(mnist_test,
                            batch_size,
                            shuffle=False,
                            num_workers=get_dataloader_workers()))


def main():
    train_iter, test_iter = load_data_fashion_mnist(32, resize=64)
    for X, y in train_iter:
        print(X.shape, X.dtype, y.shape, y.dtype)
        break


if __name__ == '__main__':
    main()
