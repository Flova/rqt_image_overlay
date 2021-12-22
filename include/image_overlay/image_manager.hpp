// Copyright 2021 Kenji Brameld
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef IMAGE_OVERLAY__IMAGE_MANAGER_HPP_
#define IMAGE_OVERLAY__IMAGE_MANAGER_HPP_

#include <QAbstractListModel>
#include <QImage>
#include <memory>
#include <string>
#include <vector>
#include "rclcpp/node.hpp"
#include "image_transport/subscriber.hpp"

class ImageManager : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit ImageManager(const rclcpp::Node::SharedPtr & node, QObject * parent = nullptr);
  std::unique_ptr<QImage> getImage() const;

protected:
  int rowCount(const QModelIndex & parent = QModelIndex()) const override;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

public slots:
  void onTopicChanged(const QString & text);
  void updateImageTopicList();

private:
  void callbackImage(const sensor_msgs::msg::Image::ConstSharedPtr & msg);

  image_transport::Subscriber subscriber_;
  const rclcpp::Node::SharedPtr & node_;
  sensor_msgs::msg::Image::ConstSharedPtr lastMsg;

  std::vector<std::string> topics;
};

#endif  // IMAGE_OVERLAY__IMAGE_MANAGER_HPP_
