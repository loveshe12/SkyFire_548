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

#ifndef OUTDOOR_PVP_SI_
#define OUTDOOR_PVP_SI_

#include "OutdoorPvP.h"

enum OutdoorPvPSISpells
{
    SI_SILITHYST_FLAG_GO_SPELL = 29518,
    SI_SILITHYST_FLAG = 29519,
    SI_TRACES_OF_SILITHYST = 29534,
    SI_CENARION_FAVOR = 30754
};

const uint32 SI_MAX_RESOURCES = 200;

const uint8 OutdoorPvPSIBuffZonesNum = 3;

const uint32 OutdoorPvPSIBuffZones[OutdoorPvPSIBuffZonesNum] = { 1377, 3428, 3429 };

const uint32 SI_AREATRIGGER_H = 4168;

const uint32 SI_AREATRIGGER_A = 4162;

const uint32 SI_TURNIN_QUEST_CM_A = 17090;

const uint32 SI_TURNIN_QUEST_CM_H = 18199;

const uint32 SI_SILITHYST_MOUND = 181597;

enum SI_WorldStates
{
    SI_GATHERED_A = 2313,
    SI_GATHERED_H = 2314,
    SI_SILITHYST_MAX = 2317
};

class OutdoorPvPSI : public OutdoorPvP
{
    public:
        OutdoorPvPSI();

        bool SetupOutdoorPvP() OVERRIDE;
        void HandlePlayerEnterZone(Player* player, uint32 zone) OVERRIDE;
        void HandlePlayerLeaveZone(Player* player, uint32 zone) OVERRIDE;
        bool Update(uint32 diff) OVERRIDE;
        void FillInitialWorldStates(WorldStateBuilder& builder) OVERRIDE;
        void SendRemoveWorldStates(Player* player) OVERRIDE;
        bool HandleAreaTrigger(Player* player, uint32 trigger) OVERRIDE;
        bool HandleDropFlag(Player* player, uint32 spellId) OVERRIDE;
        bool HandleCustomSpell(Player* player, uint32 spellId, GameObject* go) OVERRIDE;
        void UpdateWorldState();

    private:
        uint32 m_Gathered_A;
        uint32 m_Gathered_H;
        uint32 m_LastController;
};

#endif
