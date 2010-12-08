// Copyright (c) 2010, Amar Takhar <verm@aegisub.org>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// $Id$

/// @file command.cpp
/// @brief Command system base file.
/// @ingroup command

#include "command.h"
#include <libaegisub/log.h>

namespace cmd {

cmdMap cmd_map;


int id(std::string name) {

	cmdMap::iterator index;

//	if ((index = cmd_map.find(name.c_str())) != cmd_map.end()) {
//  XXX: the above does not work, wtf?
	for (index = cmd_map.begin(); index != cmd_map.end(); index++) {
		if (index->first == name) {
			int id = std::distance(cmd_map.begin(), index) + 10000;
//			printf("cmd::id %d (%s)\n", id, index->first);
			return id;
		}
	}

	printf("cmd::id NOT FOUND (%s)\n", name.c_str());
	return 60003;
}


void call(agi::Context *c, const int id) {
	cmdMap::iterator index(cmd::cmd_map.begin());
	std::advance(index, id);

	if (index != cmd::cmd_map.end()) {
		(index->second)(c);
		LOG_D("event/command") << index->first << " " << "(" << id << ")";
	} else {
		LOG_W("event/command/not_found") << "EVENT ID NOT FOUND: " << id;
	}
}

} // namespace cmd
