#!/usr/bin/env python3
################################################################
# Copyright 2021 HUST Control Science Innovation Base.
# All rights reserved.
# Author: Dong Zhaorui 847235539@qq.com
# Date  : 2021-12-06
################################################################

import os
import pandas as pd
import torch

# 创建一个人工数据集
os.makedirs(os.path.join('..', 'data'), exist_ok=True)
data_file = os.path.join('..', 'data', 'house_tiny.csv')
with open(data_file, 'w') as f:
    f.write("NumRooms,Alley,Price\n")
    f.write("NA,Pave,127500\n")
    f.write("2,NA,106000\n")
    f.write("4,NA,178100\n")
    f.write("NA,NA,140000\n")

print("###############################################################\n")
# 使用pandas读取数据
data = pd.read_csv(data_file)
# 打印
print(f"### row_data : ###\n{data}\n")

# 处理缺失的数据（一般插值或删除）此处讲插值
inputs, outputs = data.iloc[:, 0:2], data.iloc[:, 2]
print(f"### row_inputs : ###\n{inputs}\n")
print(f"### row_outputs : ###\n{outputs}\n")
# 对缺失的数据填充均值
inputs = inputs.fillna(inputs.mean())
# 对类别值或离散值，将NaN视为一个类别
inputs = pd.get_dummies(inputs, dummy_na=True)
# 打印
print(f"### processed_input : ###\n{inputs}\n")

print("###############################################################\n")
# 现在inputs和outputs的所有条目都是数值类型，可以将其专为tensor
input_tensor, output_tensor = torch.tensor(
    inputs.values), torch.tensor(outputs.values)
print(f"### input_tensor : ###\n{input_tensor}\n")
print(f"### output_tensor : ###\n{output_tensor}\n")
