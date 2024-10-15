//Sort Algorithm

/*Select Sort(increasing)
 * pseudocode
 *
 * for i from 0 to n-1
 *     find smallest number between numbers[i] and numbers[n-1]
 *     swap smallest number with numbers[i]
*/

void select_sort(int n, int numbers[])
{
    int min, min_index; // min record samllest number
    for (int i = 0; i < n; i++)
    {
        min = numbers[i];
        min_index = i;
        for (int j = i; j < n; j++)
        {
            if (numbers[j] < min)
            {
                min = numbers[j];
                min_index = j;
            }
        }
        numbers[i] = numbers[i] + min;
        numbers[min_index] = numbers[i] - numbers[min_index];
        numbers[i] = numbers[i] - numbers[min_index];
    }
}


//deep first search

/*dfs pseudocode
 *
 * marked = [false] * G.size();
 * def dfs(G, node, v)
 *     visit(v)
 *     makred[v] = ture
 *     for w in G.neibors(v)
 *         if marked[w] = false
 *             dfs(G, node, w)
*/

#define NODE node_number
bool marked[node_number] = { 0 };
void dfs(int graph[][], int node, int noded_visit)
{
    marked[noded_visit] = 1;

    for (int i = 0; i < node; i++)
    {
        if (!marked[i] && graph[noded_visit][i] == 1) // graph[i][j]表示node i和node j相连
            dfs(graph, node, i);
    }
}

/*dfs_cycle pseudocode
 * 检测图中是否存在环
 *
 * cycle = false
 * marked = G.size() * node.status()
 * for node from 0 to n-1
 *     def dfs_cycle(G, node, v)
 *         marked[v].visiting = true
 *         for w in G.neibors(v)
 *             if marked[w].visiting = true
 *                 cycle = true
 *             else if mared[w].unvisit = true
 *                 dfs_cycle(G, node, v)
 *         marked[v].visted = true
*/

#define NODE node_number
bool cycle;
int marked[node_number] = { 0 };
void dfs_cycle(int* graph, int node, int node_visit)
{
    marked[node_visit] = 1;
    for (int i = 0; i < node; i++)
    {
        if (marked[i] == 0 && graph[node_visit * node + i] == 1)
            dfs_cycle(graph, node, i);
        else if (marked[i] == 1 && graph[node_visit * node + i] == 1)
            cycle = 1;
    }
    marked[node_visit] = -1;
}
