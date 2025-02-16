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

#include "HMACSHA1.h"
#include "BigNumber.h"
#include "Common.h"

HmacHash::HmacHash(uint32 len, uint8 *seed) : m_ctx(HMAC_CTX_new())
{
    HMAC_Init_ex(m_ctx, seed, len, EVP_sha1(), NULL);
}

HmacHash::~HmacHash()
{
    HMAC_CTX_free(m_ctx);
}

void HmacHash::UpdateData(const std::string &str)
{
    HMAC_Update(m_ctx, (uint8 const*)str.c_str(), str.length());
}

void HmacHash::UpdateData(const uint8* data, size_t len)
{
    HMAC_Update(m_ctx, data, len);
}

void HmacHash::Finalize()
{
    uint32 length = 0;
    HMAC_Final(m_ctx, (uint8*)m_digest, &length);
    ASSERT(length == SHA_DIGEST_LENGTH);
}

uint8 *HmacHash::ComputeHash(BigNumber* bn)
{
    HMAC_Update(m_ctx, bn->AsByteArray(), bn->GetNumBytes());
    Finalize();
    return (uint8*)m_digest;
}
