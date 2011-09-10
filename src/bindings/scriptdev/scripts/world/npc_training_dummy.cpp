#include "precompiled.h"

#define OUT_OF_COMBAT_TIME 5000

struct MANGOS_DLL_DECL npc_training_dummyAI : public Scripted_NoMovementAI
{
    uint32 combat_timer;

    npc_training_dummyAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        Reset();
    }

    void Aggro()
    {
        m_creature->addUnitState(UNIT_STAT_STUNNED);
        m_creature->CastSpell(m_creature,23775,0);
        m_creature->CastSpell(m_creature,1908,0);
        /*DoCastSpellIfCan(m_creature, 23775);
        DoCastSpellIfCan(m_creature, 1908);
        m_creature->CastSpell(m_creature,23775,0);
        m_creature->CastSpell(m_creature,1908,0);*/
    }
    void Reset()
    {
        combat_timer = 0;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        combat_timer = 0;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_creature->SetTargetGuid(m_creature->GetObjectGuid());

        m_creature->ModifyHealth(m_creature->GetMaxHealth());

        combat_timer += diff;
        if (combat_timer > OUT_OF_COMBAT_TIME)
            EnterEvadeMode();
    }
};

CreatureAI* GetAI_npc_training_dummy(Creature* pCreature)
{
    return new npc_training_dummyAI(pCreature);
}

void AddSC_npc_training_dummy()
{
    Script *newscript = new Script;
    newscript->Name = "npc_training_dummy";
    newscript->GetAI = &GetAI_npc_training_dummy;
    newscript->RegisterSelf();
}