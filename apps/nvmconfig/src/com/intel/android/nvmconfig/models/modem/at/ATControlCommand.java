/* Android Modem NVM Configuration Tool
 *
 * Copyright (C) Intel 2012
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Edward Marmounier <edwardx.marmounier@intel.com>
 */

package com.intel.android.nvmconfig.models.modem.at;

import com.intel.android.nvmconfig.models.modem.ModemControlCommand;

public class ATControlCommand implements ModemControlCommand {

    protected String atCmd = null;

    public ATControlCommand(String atCommand) {
        if (atCommand == null || atCommand.length() <= 0) {
            throw new IllegalArgumentException("atCommand");
        }
        this.atCmd = atCommand;
        if (!this.atCmd.endsWith("\r\n")) {
            this.atCmd += "\r\n";
        }
    }

    public Object getCommand() {
        return this.atCmd;
    }

    @Override
    public String toString() {
        return this.atCmd;
    }
}