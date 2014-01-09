/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "fullpipe/fullpipe.h"

#include "fullpipe/objectnames.h"
#include "fullpipe/constants.h"

#include "fullpipe/gameloader.h"
#include "fullpipe/motion.h"
#include "fullpipe/scenes.h"
#include "fullpipe/statics.h"

#include "fullpipe/interaction.h"
#include "fullpipe/behavior.h"


namespace Fullpipe {

const int ventsInit[9] = { 0, 0, 1, 0, 0, 1, 0, 0, 1 };

void scene33_initScene(Scene *sc) {
	g_vars->scene33_var01 = 200;
	g_vars->scene33_var02 = 200;
	g_vars->scene33_var03 = 300;
	g_vars->scene33_var04 = 300;
	g_vars->scene33_mug = sc->getStaticANIObject1ById(ANI_MUG_33, -1);
	g_vars->scene33_jettie = sc->getStaticANIObject1ById(ANI_JETTIE_FLOW, -1);
	g_vars->scene33_var07 = 0;
	g_vars->scene33_var08 = -1;
	g_vars->scene33_var09 = 0;

	if (g_fp->getObjectState(sO_Cube) == g_fp->getObjectEnumState(sO_Cube, sO_In_33)) {
		MessageQueue *mq = new MessageQueue(sc->getMessageQueueById(QU_KBK33_START), 0, 0);

		mq->sendNextCommand();
	}


	for (int i = 0; i < 9; i++) {
		g_vars->scene33_ventsX[i] = sc->getStaticANIObject1ById(ANI_VENT_33, i)->_ox;

		g_vars->scene33_ventsState[i] = ventsInit[i];
	}

	g_fp->initArcadeKeys("SC_33");
}

void scene33_setupMusic() {
	if (g_fp->lift_checkButton(sO_Level6))
		g_fp->playTrack(g_fp->getGameLoaderGameVar()->getSubVarByName("SC_33"), "MUSIC2", 1);
}

int scene33_updateCursor() {
	g_fp->updateCursorCommon();

	if (g_fp->_objectIdAtCursor == PIC_SC33_ZONES && g_fp->_cursorId == PIC_CSR_DEFAULT)
		g_fp->_cursorId = PIC_CSR_ITN;

	return g_fp->_cursorId;
}

void sceneHandler33_processJettie(ExCommand *cmd) {
	warning("STUB: sceneHandler33_processJettie(cmd");
}

void sceneHandler33_processVents() {
	warning("STUB: sceneHandler33_processVents(");
}

void sceneHandler33_switchVent() {
	warning("STUB: sceneHandler33_switchVent(");
}

void sceneHandler33_tryCube() {
	warning("STUB: sceneHandler33_tryCube(");
}

void sceneHandler33_pour() {
	warning("STUB: sceneHandler33_pour(");
}

void sceneHandler33_handleDown() {
	warning("STUB: sceneHandler33_handleDown(");
}

void sceneHandler33_zoneClickProcess(StaticANIObject *ani) {
	warning("STUB: sceneHandler33_zoneClickProcess()");
}

void sceneHandler33_clickZones(ExCommand *cmd) {
	StaticANIObject *closest = 0;
	double mindist = 1e10;

	for (uint i = 0; i < g_fp->_currentScene->_staticANIObjectList1.size(); i++) {
		StaticANIObject *ani = (StaticANIObject *)g_fp->_currentScene->_staticANIObjectList1[i];

		if (ani->_id == ANI_VENT_33) {
			int dx = ani->_ox - cmd->_sceneClickX;
			int dy = ani->_oy - cmd->_sceneClickY;
			double dist = sqrt((double)(dx * dx + dy * dy));

			if (dist < mindist) {
				mindist = dist;
				closest = ani;
			}
		}
	}

	if (closest)
		sceneHandler33_zoneClickProcess(closest);
}

int sceneHandler33(ExCommand *cmd) {
	if (cmd->_messageKind != 17)
		return 0;

	switch (cmd->_messageNum) {
	case MSG_SC32_TRUBATOFRONT:
		g_fp->_currentScene->getPictureObjectById(PIC_SC33_LTRUBA, 0)->_priority = 0;
		break;

	case MSG_SC32_TRUBATOBACK:
		g_fp->_currentScene->getPictureObjectById(PIC_SC33_LTRUBA, 0)->_priority = 20;
		break;

	case MSG_SC33_TESTMUG:
		sceneHandler33_processJettie(cmd);
		break;

	case MSG_SC33_UPDATEKUBIK:
		g_vars->scene33_var07 = g_fp->_currentScene->getStaticANIObject1ById(ANI_KUBIK, -1);

		if (g_vars->scene33_var07)
			g_vars->scene33_var08 = g_vars->scene33_var07->_ox;

		break;

	case MSG_SC33_TRYKUBIK:
		sceneHandler33_tryCube();
		break;

	case MSG_SC33_POUR:
		sceneHandler33_pour();
		break;

	case MSG_SC33_HANDLEDOWN:
		sceneHandler33_handleDown();
		break;

	case 29:
		{
			StaticANIObject *ani = g_fp->_currentScene->getStaticANIObjectAtPos(g_fp->_sceneRect.left + cmd->_x, g_fp->_sceneRect.top + cmd->_y);

			if (!ani || !canInteractAny(g_fp->_aniMan, ani, cmd->_keyCode)) {
				int picId = g_fp->_currentScene->getPictureObjectIdAtPos(cmd->_sceneClickX, cmd->_sceneClickY);
				PictureObject *pic = g_fp->_currentScene->getPictureObjectById(picId, 0);

				if (pic && pic->_id == PIC_SC33_ZONES) {
					sceneHandler33_clickZones(cmd);
					break;
				}

				if (!pic || !canInteractAny(g_fp->_aniMan, pic, cmd->_keyCode)) {
					if ((g_fp->_sceneRect.right - cmd->_sceneClickX < 47 && g_fp->_sceneRect.right < g_fp->_sceneWidth - 1) || (cmd->_sceneClickX - g_fp->_sceneRect.left < 47 && g_fp->_sceneRect.left > 0))
						g_fp->processArcade(cmd);
				}
			}
			break;
		}

	case 33:
		if (g_fp->_aniMan2) {
			int x = g_fp->_aniMan2->_ox;

			if (x < g_fp->_sceneRect.left + g_vars->scene33_var01)
				g_fp->_currentScene->_x = x - g_vars->scene33_var03 - g_fp->_sceneRect.left;

			if (x > g_fp->_sceneRect.right - g_vars->scene33_var01)
				g_fp->_currentScene->_x = x + g_vars->scene33_var03 - g_fp->_sceneRect.right;
		}

		if (g_vars->scene33_var07)
			sceneHandler33_processVents();

		g_fp->_behaviorManager->updateBehaviors();

		g_fp->startSceneTrack();

		break;
	}

	return 0;
}

} // End of namespace Fullpipe
