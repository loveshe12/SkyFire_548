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
#include "violet_hold.h"

enum Spells
{
    SPELL_ARCANE_VACUUM                         = 58694,
    SPELL_BLIZZARD                              = 58693,
    H_SPELL_BLIZZARD                            = 59369,
    SPELL_MANA_DESTRUCTION                      = 59374,
    SPELL_TAIL_SWEEP                            = 58690,
    H_SPELL_TAIL_SWEEP                          = 59283,
    SPELL_UNCONTROLLABLE_ENERGY                 = 58688,
    H_SPELL_UNCONTROLLABLE_ENERGY               = 59281,
    SPELL_TRANSFORM                             = 58668
};

enum Yells
{
    SAY_AGGRO                                   = 0,
    SAY_SLAY                                    = 1,
    SAY_DEATH                                   = 2,
    SAY_SPAWN                                   = 3,
    SAY_DISRUPTION                              = 4,
    SAY_BREATH_ATTACK                           = 5,
    SAY_SPECIAL_ATTACK                          = 6
};

class boss_cyanigosa : public CreatureScript
{
public:
    boss_cyanigosa() : CreatureScript("boss_cyanigosa") { }

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new boss_cyanigosaAI(creature);
    }

    struct boss_cyanigosaAI : public ScriptedAI
    {
        boss_cyanigosaAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        uint32 uiArcaneVacuumTimer;
        uint32 uiBlizzardTimer;
        uint32 uiManaDestructionTimer;
        uint32 uiTailSweepTimer;
        uint32 uiUncontrollableEnergyTimer;

        InstanceScript* instance;

        void Reset() OVERRIDE
        {
            uiArcaneVacuumTimer = 10000;
            uiBlizzardTimer = 15000;
            uiManaDestructionTimer = 30000;
            uiTailSweepTimer = 20000;
            uiUncontrollableEnergyTimer = 25000;
            if (instance)
                instance->SetData(DATA_CYANIGOSA_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/) OVERRIDE
        {
            Talk(SAY_AGGRO);

            if (instance)
                instance->SetData(DATA_CYANIGOSA_EVENT, IN_PROGRESS);
        }

        void MoveInLineOfSight(Unit* /*who*/) OVERRIDE { }


        void UpdateAI(uint32 diff) OVERRIDE
        {
            if (instance && instance->GetData(DATA_REMOVE_NPC) == 1)
            {
                me->DespawnOrUnsummon();
                instance->SetData(DATA_REMOVE_NPC, 0);
            }

            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (uiArcaneVacuumTimer <= diff)
            {
                DoCast(SPELL_ARCANE_VACUUM);
                uiArcaneVacuumTimer = 10000;
            } else uiArcaneVacuumTimer -= diff;

            if (uiBlizzardTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_BLIZZARD);
                uiBlizzardTimer = 15000;
            } else uiBlizzardTimer -= diff;

            if (uiTailSweepTimer <= diff)
            {
                DoCast(SPELL_TAIL_SWEEP);
                uiTailSweepTimer = 20000;
            } else uiTailSweepTimer -= diff;

            if (uiUncontrollableEnergyTimer <= diff)
            {
                DoCastVictim(SPELL_UNCONTROLLABLE_ENERGY);
                uiUncontrollableEnergyTimer = 25000;
            } else uiUncontrollableEnergyTimer -= diff;

            if (IsHeroic())
            {
                if (uiManaDestructionTimer <= diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(target, SPELL_MANA_DESTRUCTION);
                    uiManaDestructionTimer = 30000;
                } else uiManaDestructionTimer -= diff;
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/) OVERRIDE
        {
            Talk(SAY_DEATH);

            if (instance)
                instance->SetData(DATA_CYANIGOSA_EVENT, DONE);
        }

        void KilledUnit(Unit* victim) OVERRIDE
        {
            if (victim->GetTypeId() != TypeID::TYPEID_PLAYER)
                return;

            Talk(SAY_SLAY);
        }
    };
};

class achievement_defenseless : public AchievementCriteriaScript
{
    public:
        achievement_defenseless() : AchievementCriteriaScript("achievement_defenseless")
        {
        }

        bool OnCheck(Player* /*player*/, Unit* target) OVERRIDE
        {
            if (!target)
                return false;

            InstanceScript* instance = target->GetInstanceScript();
            if (!instance)
                return false;

            if (!instance->GetData(DATA_DEFENSELESS))
                return false;

            return true;
        }
};

void AddSC_boss_cyanigosa()
{
    new boss_cyanigosa();
    new achievement_defenseless();
}
