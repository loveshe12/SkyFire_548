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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum Spells
{
    SPELL_MIGHTYBLOW                                       = 14099,
    SPELL_HAMSTRING                                        = 9080,
    SPELL_CLEAVE                                           = 20691
};

class boss_general_angerforge : public CreatureScript
{
public:
    boss_general_angerforge() : CreatureScript("boss_general_angerforge") { }

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new boss_general_angerforgeAI(creature);
    }

    struct boss_general_angerforgeAI : public ScriptedAI
    {
        boss_general_angerforgeAI(Creature* creature) : ScriptedAI(creature) { }

        uint32 MightyBlow_Timer;
        uint32 HamString_Timer;
        uint32 Cleave_Timer;
        uint32 Adds_Timer;
        bool Medics;

        void Reset() OVERRIDE
        {
            MightyBlow_Timer = 8000;
            HamString_Timer = 12000;
            Cleave_Timer = 16000;
            Adds_Timer = 0;
            Medics = false;
        }

        void EnterCombat(Unit* /*who*/) OVERRIDE { }

        void SummonAdds(Unit* victim)
        {
            if (Creature* SummonedAdd = DoSpawnCreature(8901, float(irand(-14, 14)), float(irand(-14, 14)), 0, 0, TempSummonType::TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120000))
                SummonedAdd->AI()->AttackStart(victim);
        }

        void SummonMedics(Unit* victim)
        {
            if (Creature* SummonedMedic = DoSpawnCreature(8894, float(irand(-9, 9)), float(irand(-9, 9)), 0, 0, TempSummonType::TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120000))
                SummonedMedic->AI()->AttackStart(victim);
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //MightyBlow_Timer
            if (MightyBlow_Timer <= diff)
            {
                DoCastVictim(SPELL_MIGHTYBLOW);
                MightyBlow_Timer = 18000;
            } else MightyBlow_Timer -= diff;

            //HamString_Timer
            if (HamString_Timer <= diff)
            {
                DoCastVictim(SPELL_HAMSTRING);
                HamString_Timer = 15000;
            } else HamString_Timer -= diff;

            //Cleave_Timer
            if (Cleave_Timer <= diff)
            {
                DoCastVictim(SPELL_CLEAVE);
                Cleave_Timer = 9000;
            } else Cleave_Timer -= diff;

            //Adds_Timer
            if (HealthBelowPct(21))
            {
                if (Adds_Timer <= diff)
                {
                    // summon 3 Adds every 25s
                    SummonAdds(me->GetVictim());
                    SummonAdds(me->GetVictim());
                    SummonAdds(me->GetVictim());

                    Adds_Timer = 25000;
                } else Adds_Timer -= diff;
            }

            //Summon Medics
            if (!Medics && HealthBelowPct(21))
            {
                SummonMedics(me->GetVictim());
                SummonMedics(me->GetVictim());
                Medics = true;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_general_angerforge()
{
    new boss_general_angerforge();
}
