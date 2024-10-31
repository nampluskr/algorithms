### mnist_clf10_traniner.py

```python
import os
import numpy as np
import gzip

import sys
import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
from tqdm import tqdm
from copy import deepcopy


## MNIST
def load_mnist_images(data_dir, filename):
    data_path = os.path.join(data_dir, filename)
    with gzip.open(data_path, 'rb') as f:
        data = np.frombuffer(f.read(), np.uint8, offset=16)
    return data.reshape(-1, 28, 28)

def load_mnist_labels(data_dir, filename):
    data_path = os.path.join(data_dir, filename)
    with gzip.open(data_path, 'rb') as f:
        data = np.frombuffer(f.read(), np.uint8, offset=8)
    return data

def load_mnist(data_dir):
    train_images = load_mnist_images(data_dir, "train-images-idx3-ubyte.gz")
    train_labels = load_mnist_labels(data_dir, "train-labels-idx1-ubyte.gz")
    test_images = load_mnist_images(data_dir, "t10k-images-idx3-ubyte.gz")
    test_labels = load_mnist_labels(data_dir, "t10k-labels-idx1-ubyte.gz")
    return (train_images, train_labels), (test_images, test_labels)


class MNIST(Dataset):
    def __init__(self, images, labels):
        self.images = images / 255.0
        self.labels = labels

    def __len__(self):
        return len(self.images)

    def __getitem__(self, idx):
        image = self.images[idx]
        label = self.labels[idx]
        image = torch.tensor(image).float().unsqueeze(dim=0)    # (N, 1, 28, 28)
        label = torch.tensor(label).long()
        return image, label


## Model
class MLP(nn.Module):
    def __init__(self, n_classes):
        super().__init__()
        self.flatten = nn.Flatten()
        self.fc = nn.Sequential(
            nn.Linear(28*28, 512),
            nn.ReLU(),
            nn.Linear(512, 256),
            nn.ReLU(),
            nn.LayerNorm(256),
            nn.Linear(256, n_classes),
        )

    def forward(self, x):
        x = self.flatten(x)
        logits = self.fc(x)
        return logits


class CNN(nn.Module):
    def __init__(self, n_classes):
        super().__init__()
        self.conv1 = nn.Conv2d(1, 6, 5)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16 * 4 * 4, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, n_classes)

    def forward(self, x):
        x = x.view(-1, 1, 28, 28)
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 16 * 4 * 4)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        logits = self.fc3(x)
        return logits


def accuracy(y_pred, y_true):
    y_pred = y_pred.argmax(dim=1)   # int64 (long)
    return torch.eq(y_pred, y_true).float().mean()



if __name__ == "__main__":

    from trainer import EarlyStopping, Trainer
    from trainer import set_seed, save_model, save_history


    set_seed(42)

    ## Hyperparameters
    batch_size = 64
    n_epochs = 100
    learning_rate = 1e-3
    lr_scheduling = False
    early_stopping = True
    model_dir = "./"
    model_name = "mnist_clf10_20241031"
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    ## Load Data
    data_dir = r"/home/namu/myspace/NAMU/datasets/fashion_mnist/"
    train_data, test_data = load_mnist(data_dir)

    train_images, train_labels = train_data
    test_images, test_labels = test_data

    print("\n>> Dataset:")
    print(f"train_images: {train_images.shape}")
    print(f"train_labels: {train_labels.shape}")

    train_dataset = MNIST(train_images, train_labels)
    test_dataset = MNIST(test_images, test_labels)

    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

    ## Train model
    # model = MLP(n_classes=10).to(device)
    model = CNN(n_classes=10).to(device)
    loss_fn = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=learning_rate)
    metrics = {"acc": accuracy}

    print("\n>> Training:")
    clf = Trainer(model, optimizer, loss_fn, metrics=metrics)

    stopper = EarlyStopping(patience=3, min_delta=0.001) \
        if early_stopping else None
    scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=5, gamma=0.5) \
        if lr_scheduling else None

    hist = clf.fit(train_loader, n_epochs, valid_loader=test_loader,
                   stopper=stopper, scheduler=scheduler)
    res = clf.evaluate(test_loader)

    save_model(model, model_dir, model_name)
    save_history(hist, model_dir, model_name)
```