/**
 * Copy right YMSys, 2015,2016 Zhaoming Yin
 *
 * @brief    This is the class for CSR formatted graph. 
 *
 *  MODIFIED   (MM/DD/YY)
 *  stplaydog   02/09/16 - Creation
 *
**/

/**
 * @brief       build graph from ny crime data
 **/
void CrimeSTModel::read_data()
{
    ifstream reader(input_file);
    struct tm tm;
    string line;

    while(getline(reader, line))
    {
        Node n;
        n.id = serial_num++;

        isstringstream iss(line);

        string token;

        getline(iss, token, ',');
        strptime(token.c_str(),"%Y/%M/%D", &tm); 
        n.ts = mktime(tm);

        getline(iss, token, ',');
        n.xx[0] = n.xx[1] = stoi(token);

        getline(iss, token, ',');
        n.yy[0] = n.yy[1] = stoi(token);

        getline(iss, token, ',');
        n.freq = stoi(token);

        getline(iss, n.type, ',');

        nodes.push_back(n);
    }
}

/**
 * @brief       build graph from ny crime data
 **/
void CrimeSTModel::build_model()
{
    RTree<void*, int, 3, float> rt;

    for(int i=0; i<nodes.size(); i++)
    {
        rt.Insert(nodes[i].min, nodes[i].max, &(nodes[i]));
    } 
}

vector<int32_t> query(int32_t max[2], int32_t min[2], time_t ts[2])
{
}

vector<int32_t> query(int32_t x, int32_t y, time_t ts, 
        int32_t cord_range, time_t time_range)
{
}
