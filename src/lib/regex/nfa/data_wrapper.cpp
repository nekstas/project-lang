#include "data_wrapper.h"

#include "../../errors/errors.h"
#include "data.h"
#include "state_wrapper.h"

namespace lang::regex::nfa {

DataWrapper::DataWrapper() {
    InitRoot();
}

const Data& DataWrapper::GetData() const {
    return data_;
}

void DataWrapper::Clear() {
    data_.states_.clear();
    InitRoot();
}

StateWrapper DataWrapper::GetState(size_t node_id) {
    THROW_IF(node_id >= data_.Size(), ::errors::LogicError,
             "node_id " << node_id << "is out of range (size = " << data_.Size() << ").");
    return {node_id, this};
}

StateWrapper DataWrapper::CreateState() {
    size_t node_id = data_.states_.size();
    data_.states_.emplace_back();
    return {node_id, this};
}

void DataWrapper::InitRoot() {
    THROW_IF(!data_.states_.empty(), ::errors::LogicError,
             "Can't init a NFA if it already has states.");
    CreateState();
}

StateWrapper DataWrapper::GetRoot() {
    THROW_IF(data_.states_.empty(), ::errors::LogicError,
             "Can't get a NFA's root, because it is empty.");
    return GetState(0);
}

State& DataWrapper::ExtractState(StateWrapper state) {
    THROW_IF(state.data_ != this, ::errors::LogicError,
             "Trying to extract state from different data.");
    THROW_IF(state.state_id_ >= data_.Size(), ::errors::LogicError,
             "Trying to extract state with index (" << state.state_id_ << ") while there are "
                                                    << data_.Size() << " states.");
    return data_.states_[state.state_id_];
}

size_t DataWrapper::NextFinalId() {
    return data_.final_states_number_++;
}

}  // namespace lang::regex::nfa
