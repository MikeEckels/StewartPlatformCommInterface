using Simvars;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace SimWatcher
{
    interface SysVarLoaderInterface
    {
        void loadSysVariables();
        List<object> getVarsAndUnits();
        void setTxtFileLocation(String location);
        String getTxtFileLocation();
    }


    public class SysVarLoader : SysVarLoaderInterface
    {
        private Hashtable table;
        private String txtFile;

        public SysVarLoader()
        {
            table = new Hashtable();
        }

        public void setTxtFileLocation(String location)
        {
            if (!File.Exists(location))
            {
                throw new FileNotFoundException("Data file is missing");
            }
            txtFile = location;
        }

        public String getTxtFileLocation()
        {
            return this.txtFile;
        }

        public void loadSysVariables()
        {
            StreamReader sr = new StreamReader(this.txtFile);
            String line;

            while ((line = sr.ReadLine()) != null)
            {
                table.Add(line, null);
            }
            sr.Close();
        }

        public void setKeyValue(String key, object val){
            this.table[key] = val;
        }

        public List<object> getVarsAndUnits()
        {
            List<object> ret = new List<object>();
            String[] keys = new string[table.Count];
            table.Keys.CopyTo(keys, 0);

            for (int i = 0; i < keys.Length; i++)
            {
                ret.Add(new keyUnit(keys[i], "meters per second"));
            }

            return ret;
        }

        public Hashtable getTable(){
            return this.table;
        }
    }
}
