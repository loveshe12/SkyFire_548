/*
 * Copyright (C) 2011-2022 Project SkyFire <https://www.projectskyfire.org/>
 * Copyright (C) 2008-2022 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2022 MaNGOS <https://www.getmangos.eu/>
 * Copyright (C) 2006-2014 ScriptDev2 <https://github.com/scriptdev2/scriptdev2/>
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

#ifndef DEF_BRD_H
#define DEF_BRD_H

enum FactionIds
{
    FACTION_NEUTRAL            = 734,
    FACTION_HOSTILE            = 754,
    FACTION_FRIEND             = 35
};

enum DataTypes
{
    TYPE_RING_OF_LAW        = 1,
    TYPE_VAULT              = 2,
    TYPE_BAR                = 3,
    TYPE_TOMB_OF_SEVEN      = 4,
    TYPE_LYCEUM             = 5,
    TYPE_IRON_HALL          = 6,

    DATA_EMPEROR            = 10,
    DATA_PHALANX            = 11,

    DATA_ARENA1             = 12,
    DATA_ARENA2             = 13,
    DATA_ARENA3             = 14,
    DATA_ARENA4             = 15,

    DATA_GO_BAR_KEG         = 16,
    DATA_GO_BAR_KEG_TRAP    = 17,
    DATA_GO_BAR_DOOR        = 18,
    DATA_GO_CHALICE         = 19,

    DATA_GHOSTKILL          = 20,
    DATA_EVENSTARTER        = 21,

    DATA_GOLEM_DOOR_N       = 22,
    DATA_GOLEM_DOOR_S       = 23,

    DATA_THRONE_DOOR        = 24,

    DATA_SF_BRAZIER_N       = 25,
    DATA_SF_BRAZIER_S       = 26,
    DATA_MOIRA              = 27,
};

#endif
