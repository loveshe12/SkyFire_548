/*
 * Copyright (C) 2011-2022 Project SkyFire <https://www.projectskyfire.org/>
 * Copyright (C) 2008-2022 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2022 MaNGOS <https://www.getmangos.eu/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SF_SKYFIRE_CHANNELMGR_H
#define SF_SKYFIRE_CHANNELMGR_H

#include "Common.h"
#include "Channel.h"
#include <ace/Singleton.h>

#include <map>
#include <string>

#include "World.h"

class ChannelMgr
{
    typedef std::map<std::wstring, Channel*> ChannelMap;

    public:
        ChannelMgr() : team(0)
        { }

        ~ChannelMgr();

        static ChannelMgr * forTeam(uint32 team);
        void setTeam(uint32 newTeam) { team = newTeam; }

        Channel* GetJoinChannel(std::string const& name, uint32 channel_id);
        Channel* GetChannel(std::string const& name, Player* p, bool pkt = true);
        void LeftChannel(std::string const& name);

    private:
        ChannelMap channels;
        uint32 team;

        void MakeNotOnPacket(WorldPacket* data, std::string const& name);
};

class AllianceChannelMgr : public ChannelMgr { };
class HordeChannelMgr    : public ChannelMgr { };

#endif
