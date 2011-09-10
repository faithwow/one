#include "precompiled.h"

struct MANGOS_DLL_DECL npc_training_dummyAI : public Scripted_NoMovementAI
{
    uint32 combat_timer;

    npc_training_dummyAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        Reset();
    }

    void Reset()
    {
        m_creature->addUnitState(UNIT_STAT_STUNNED);
        m_creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
        combat_timer = 0;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        m_creature->ModifyHealth(m_creature->GetMaxHealth()/5);
        combat_timer = 0;
    }

    void UpdateAI(const uint32 diff)
    {
        combat_timer = combat_timer+diff;
        if (combat_timer > 5000)
        {
            ScriptedAI::EnterEvadeMode();
            combat_timer = 0;
        }
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