#pragma once
#ifndef LIBREALSENSE_UVC_H
#define LIBREALSENSE_UVC_H

#include "types.h"

#include <functional>

namespace rsimpl
{
    namespace uvc
    {
        struct guid
        {
            uint32_t data1;
            uint16_t data2;
            uint16_t data3;
            uint8_t data4[8];
        };

        struct device_ref
        {
            struct _impl; std::shared_ptr<_impl> impl;
            explicit operator bool () const { return static_cast<bool>(impl); }

            int get_vendor_id() const;
            int get_product_id() const;

            void claim_interface(const guid & interface_guid, int interface_number) const;
            void bulk_transfer(unsigned char endpoint, void * data, int length, int *actual_length, unsigned int timeout) const;

            void get_control(uint8_t unit, uint8_t ctrl, void * data, int len) const;
            void set_control(uint8_t unit, uint8_t ctrl, void * data, int len) const;

            void set_subdevice_mode(int subdevice_index, int width, int height, uint32_t fourcc, int fps, std::function<void(const void * frame)> callback) const;
            void start_streaming() const;
            void stop_streaming() const;
        };

        struct context_ref
        {
            struct _impl; std::shared_ptr<_impl> impl;
            explicit operator bool () const { return static_cast<bool>(impl); }

            std::vector<device_ref> query_devices() const;
        };

        context_ref create_context();
    }
}

#endif