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

    }
    void Reset()
    {
        combat_timer = 0;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        m_creature->SetTargetGuid(ObjectGuid());
        combat_timer = 0;
    }

    void UpdateAI(const uint32 diff)
    {
        m_creature->SetTargetGuid(ObjectGuid());
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

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