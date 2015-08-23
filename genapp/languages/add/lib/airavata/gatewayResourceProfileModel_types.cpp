/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "gatewayResourceProfileModel_types.h"

#include <algorithm>

namespace apache { namespace airavata { namespace model { namespace appcatalog { namespace gatewayprofile {

const char* ComputeResourcePreference::ascii_fingerprint = "D89E0E13D04B60B99B78496AC9B85D52";
const uint8_t ComputeResourcePreference::binary_fingerprint[16] = {0xD8,0x9E,0x0E,0x13,0xD0,0x4B,0x60,0xB9,0x9B,0x78,0x49,0x6A,0xC9,0xB8,0x5D,0x52};

uint32_t ComputeResourcePreference::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_computeResourceId = false;
  bool isset_overridebyAiravata = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->computeResourceId);
          isset_computeResourceId = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->overridebyAiravata);
          isset_overridebyAiravata = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->loginUserName);
          this->__isset.loginUserName = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast0;
          xfer += iprot->readI32(ecast0);
          this->preferredJobSubmissionProtocol = ( ::apache::airavata::model::appcatalog::computeresource::JobSubmissionProtocol::type)ecast0;
          this->__isset.preferredJobSubmissionProtocol = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast1;
          xfer += iprot->readI32(ecast1);
          this->preferredDataMovementProtocol = ( ::apache::airavata::model::appcatalog::computeresource::DataMovementProtocol::type)ecast1;
          this->__isset.preferredDataMovementProtocol = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->preferredBatchQueue);
          this->__isset.preferredBatchQueue = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->scratchLocation);
          this->__isset.scratchLocation = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 8:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->allocationProjectNumber);
          this->__isset.allocationProjectNumber = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_computeResourceId)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_overridebyAiravata)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t ComputeResourcePreference::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("ComputeResourcePreference");

  xfer += oprot->writeFieldBegin("computeResourceId", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->computeResourceId);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("overridebyAiravata", ::apache::thrift::protocol::T_BOOL, 2);
  xfer += oprot->writeBool(this->overridebyAiravata);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.loginUserName) {
    xfer += oprot->writeFieldBegin("loginUserName", ::apache::thrift::protocol::T_STRING, 3);
    xfer += oprot->writeString(this->loginUserName);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.preferredJobSubmissionProtocol) {
    xfer += oprot->writeFieldBegin("preferredJobSubmissionProtocol", ::apache::thrift::protocol::T_I32, 4);
    xfer += oprot->writeI32((int32_t)this->preferredJobSubmissionProtocol);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.preferredDataMovementProtocol) {
    xfer += oprot->writeFieldBegin("preferredDataMovementProtocol", ::apache::thrift::protocol::T_I32, 5);
    xfer += oprot->writeI32((int32_t)this->preferredDataMovementProtocol);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.preferredBatchQueue) {
    xfer += oprot->writeFieldBegin("preferredBatchQueue", ::apache::thrift::protocol::T_STRING, 6);
    xfer += oprot->writeString(this->preferredBatchQueue);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.scratchLocation) {
    xfer += oprot->writeFieldBegin("scratchLocation", ::apache::thrift::protocol::T_STRING, 7);
    xfer += oprot->writeString(this->scratchLocation);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.allocationProjectNumber) {
    xfer += oprot->writeFieldBegin("allocationProjectNumber", ::apache::thrift::protocol::T_STRING, 8);
    xfer += oprot->writeString(this->allocationProjectNumber);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ComputeResourcePreference &a, ComputeResourcePreference &b) {
  using ::std::swap;
  swap(a.computeResourceId, b.computeResourceId);
  swap(a.overridebyAiravata, b.overridebyAiravata);
  swap(a.loginUserName, b.loginUserName);
  swap(a.preferredJobSubmissionProtocol, b.preferredJobSubmissionProtocol);
  swap(a.preferredDataMovementProtocol, b.preferredDataMovementProtocol);
  swap(a.preferredBatchQueue, b.preferredBatchQueue);
  swap(a.scratchLocation, b.scratchLocation);
  swap(a.allocationProjectNumber, b.allocationProjectNumber);
  swap(a.__isset, b.__isset);
}

const char* GatewayResourceProfile::ascii_fingerprint = "106DE1CD0F7026F6471DE8DAF360BE03";
const uint8_t GatewayResourceProfile::binary_fingerprint[16] = {0x10,0x6D,0xE1,0xCD,0x0F,0x70,0x26,0xF6,0x47,0x1D,0xE8,0xDA,0xF3,0x60,0xBE,0x03};

uint32_t GatewayResourceProfile::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_gatewayID = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->gatewayID);
          isset_gatewayID = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->computeResourcePreferences.clear();
            uint32_t _size2;
            ::apache::thrift::protocol::TType _etype5;
            xfer += iprot->readListBegin(_etype5, _size2);
            this->computeResourcePreferences.resize(_size2);
            uint32_t _i6;
            for (_i6 = 0; _i6 < _size2; ++_i6)
            {
              xfer += this->computeResourcePreferences[_i6].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.computeResourcePreferences = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_gatewayID)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t GatewayResourceProfile::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("GatewayResourceProfile");

  xfer += oprot->writeFieldBegin("gatewayID", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->gatewayID);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.computeResourcePreferences) {
    xfer += oprot->writeFieldBegin("computeResourcePreferences", ::apache::thrift::protocol::T_LIST, 2);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->computeResourcePreferences.size()));
      std::vector<ComputeResourcePreference> ::const_iterator _iter7;
      for (_iter7 = this->computeResourcePreferences.begin(); _iter7 != this->computeResourcePreferences.end(); ++_iter7)
      {
        xfer += (*_iter7).write(oprot);
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(GatewayResourceProfile &a, GatewayResourceProfile &b) {
  using ::std::swap;
  swap(a.gatewayID, b.gatewayID);
  swap(a.computeResourcePreferences, b.computeResourcePreferences);
  swap(a.__isset, b.__isset);
}

}}}}} // namespace
