public class Graph{
	private int[][] adjMat;
	private int numVerts;
	public Graph(int[][] mat, int numVerts){
		this.adjMat = mat;
		this.numVerts = numVerts;
	}

	public int[][] getAdjMat(){
		return this.adjMat;
	}
	public int getNumVerts(){
		return this.numVerts;
	}	

}
