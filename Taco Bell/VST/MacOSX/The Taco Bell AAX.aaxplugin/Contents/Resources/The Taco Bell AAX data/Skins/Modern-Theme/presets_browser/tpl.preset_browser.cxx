namespace PresetBrowser
{
    // utility to replace a string
    void replaceString(string & ioString, const string &in stringToFind, const string &in replace)
    {
        array<string>@ pieces = ioString.split(stringToFind);
        if (@pieces != null)
        {
            if (pieces.length > 0)
                ioString = pieces[0];
            for (uint i = 1; i < pieces.length; i++)
            {
                ioString += replace;
                ioString += pieces[i];
            }
        }
    }

    // cleans path separators
    string cleanPath(const string& in path)
    {
        string oPath=path;
        string sep=getFilePathSeparator();
        if (sep == "\\")
            replaceString(oPath,"/","\\");
        else
            replaceString(oPath,"\\","/");
        return oPath;
    }
}