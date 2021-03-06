/*
 * Copyright (C) 2014 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CAMERA3_HAL_MEDIACONTROLLER_H_
#define CAMERA3_HAL_MEDIACONTROLLER_H_

#include <utils/KeyedVector.h>
#include <utils/String8.h>
#include <utils/RefBase.h>
#include <linux/media.h>

namespace android {
namespace camera2 {

class MediaEntity;

/**
 * \class MediaController
 *
 * This class is used for discovering and configuring the internal topology
 * of a media device. Devices are modelled as an oriented graph of building
 * blocks called media entities. The media entities are connected to each other
 * through pads.
 *
 * Each media entity corresponds to a V4L2 subdevice. This class is also used
 * for configuring the V4L2 subdevices.
 */
class MediaController: public RefBase
{

public:
    MediaController(const char *name);
    ~MediaController();

    status_t init();

    status_t getMediaEntity(sp<MediaEntity> &entity, const char* name);
    status_t resetLinks();
    status_t configureLink(const char* srcName, int srcPad, const char* sinkName, int sinkPad, bool enable);
    status_t setFormat(const char* entityName, int pad, int width, int height, int formatCode);
    status_t setSelection(const char* entityName, int pad, int target, int top, int left, int width, int height);
    status_t setControl(const char* entityName, int controlId, int value, const char *controlName);

private:
    status_t open();
    status_t close();
    int xioctl(int request, void *arg) const;

    status_t getDeviceInfo();
    status_t findEntities();
    status_t findMediaEntityByName(char const* entityName, struct media_entity_desc &entity);
    status_t findMediaEntityById(int index, struct media_entity_desc &entity);

    status_t enumLinks(struct media_links_enum &linkInfo);
    status_t setupLink(struct media_link_desc &link);

private:
    String8      mName;     /*!< path to device in file system, ex: /dev/media0 */
    int          mFd;       /*!< file descriptor obtained when device is open */

    struct media_device_info                        mDeviceInfo;        /*!< media controller device info */
    KeyedVector<String8, struct media_entity_desc>  mEntityDesciptors;  /*!< media entity descriptors, Key: entity name */
    KeyedVector<String8, sp<MediaEntity> >          mEntities;          /*!< MediaEntities, Key: entity name */

}; // class MediaController

}; // namespace camera2
}; // namespace android

#endif
