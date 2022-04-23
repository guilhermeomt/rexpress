#include "invitation.h"

Invitation::Invitation()
{

}

Invitation::Invitation(Invitation* i)
    : m_id(i->getId()),
      m_inviterId(i->getInviterId()),
      m_inviteeId(i->getInviteeId()),
      m_projectId(i->getProjectId()),
      m_status(i->getStatus()),
      m_createdAt(i->getCreatedAt()) {}
