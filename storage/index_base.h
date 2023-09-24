#pragma once

#include "global.h"
#include "helper.h"

class table_t;

class index_base {
public:
	virtual RC 			init() { return RCOK; };
	virtual RC 			init(uint64_t size) { return RCOK; };

	virtual bool 		index_exist(idx_key_t key)=0; // check if the key exist.

	virtual RC 			index_insert(idx_key_t key,
							itemid_t * item,
							int part_id=-1)=0;

	virtual RC	 		index_read(idx_key_t key,
							itemid_t * &item,
							int part_id=-1)=0;

	virtual RC	 		index_read(idx_key_t key,
							itemid_t * &item,
							int part_id=-1, uint64_t thd_id=0)=0;

	// TODO implement index_remove
	virtual RC 			index_remove(idx_key_t key) { return RCOK; };

	// the index in on "table". The key is the merged key of "fields"
	table_t * 			table;
};

template <typename T>
concept IsIndex =
	requires(T idx, itemid_t* &item) {
		{ idx.table };
		{ idx.init() } -> std::same_as<RC>;
		{ idx.init(uint64_t()) } -> std::same_as<RC>;
		{ idx.index_exist(idx_key_t()) } -> std::same_as<bool>;
		{ idx.index_insert(idx_key_t(), item, int()) } -> std::same_as<RC>;
		{ idx.index_read(idx_key_t(), item, int()) } -> std::same_as<RC>;
		{ idx.index_read(idx_key_t(), item, int(), uint64_t()) } -> std::same_as<RC>;
		{ idx.index_remove(idx_key_t()) } -> std::same_as<RC>;
	};