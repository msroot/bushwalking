<?php
/**
 * model Class
 *
 * Main class for model, used to perform common CRUD operation on the database tables
 * Maps a table of the database to an Associative array representing the model object.
 *
 * @author Victor Nava
 *
 */
class model {
	public static $dbCon;
	public $tableName = 'model';
	public $tableCols;
	public $pageSize = 10;
	public $primaryKey = "id";

	/**
	 * Constructor
	 *
	 * @param $tableName table associated with the model
	 * @return Associative Array Attributes and Values of table
	 */
	function __construct($tableName=null){
		if($tableName){
			$this->tableName = $tableName;
		}
		//FIXME opening multiple connection everytime a model is created
		$this->dbCon = $this->PDOConnection();
		$this->dbCon->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		$this->tableCols = $this->getTableColumns($this->tableName);
	}

	/**
	 * Gets a single record from the db by id
	 * @param $id
	 * @return Associative Array Attributes and Values of table
	 */
	function get($id){
		$this->dbCon = self::PDOConnection();
        //TODO parameters and values should be passed as argument
        //so that for example get by name should be posible
        $sql = "SELECT * FROM $this->tableName WHERE id=:id";
        $stmt = $this->dbCon->prepare($sql);
        $params = array(':id'=>$id);
        $stmt->execute($params);
        return $stmt->fetch(PDO::FETCH_OBJ);
	}
	
	
	function getAllBy($col, $val){
		$sql = "SELECT * FROM $this->tableName WHERE $col=:val";
		$stmt = $this->dbCon->prepare($sql);
		$params = array(':val'=>$val);
		$stmt->execute($params);
		return $stmt->fetchAll(PDO::FETCH_OBJ);
	}
		
	/**
	 * Gets all the records of a table
	 *
	 * @param $args page
	 * @return Associative Array Attributes and Values of table
	 */
	function getAll($args = null){
		$this->dbCon = self::PDOConnection();
		
		$sql = "SELECT * FROM $this->tableName";
		
		if(isset($args['page'])){
			$page = (int)$args['page'];
			$from = $page * $this->pageSize;
			$sql = "SELECT * FROM $this->tableName LIMIT $from, $this->pageSize";
		}
		return $this->dbCon->query($sql)->fetchAll(PDO::FETCH_OBJ);
	}

	/**
	 * Creates a record in the table
	 *
	 * @param $args
	 * @return Associative Array Attributes and Values of created record
	 */
	function create($args=null){

		//TODO check if already exist
		if(!isset($args)){
			return false;
		}

		//TODO make function get colVals;
		foreach($args as $col=>$val){
			if($col != 'id'){
				if(in_array($col, $this->tableCols)){
					$columns[] = $col;
					$values[] = is_numeric($val) ? $val : "'".$val."'";
				}
			}
		}

		if(!isset($columns)){
			return false;
		}

		$sqlInsert = "INSERT INTO ".$this->tableName." (".implode(",", $columns) . ') VALUES ('.implode(",", $values).')';
		$sqlLast = "SELECT * FROM $this->tableName ORDER BY $this->primaryKey DESC LIMIT 1";
		//echo $sqlLast;

		//TODO this should be a transaction
		$rowCount = $this->dbCon->exec($sqlInsert);
		if($rowCount < 1){
			return false;
		}
		return $this->dbCon->query($sqlLast)->fetchAll(PDO::FETCH_OBJ);	
	}

	/**
	 * Updates a record in the table
	 *
	 * @param $args
	 * @return Associative Array Attributes and Values of updated record
	 */
	function update($args=null){

		if(!isset($args) || !isset($args['id'])){
			return false;
		}

		foreach($args as $col=>$val){
			if($col != 'id'){
				if(in_array($col, $this->tableCols)){
					$colsAndVals[] = $col .'=' . (is_numeric($val) ? $val : "'".$val."'");
				}
			}
		}

		if(!isset($colsAndVals)){
			return false;
		}

		$id = $args['id'];
		$colsAndValsStr = implode(',', $colsAndVals);
		$table = $this->tableName;
			
		$sql = "UPDATE $table SET $colsAndValsStr WHERE (id=$id)";
		
		return $this->dbCon->exec($sql);
	}

	function delete($id){
		$sql = "DELETE FROM $this->tableName WHERE (id=$id)";
		return $this->dbCon->exec($sql);
	}

	/**
	 * Get all the columns name of the table
	 * @param $tableName
	 * @return Array Names of columns
	 */
	function getTableColumns($tableName){
		//echo "getTableColumns($tableName)";
		$desc = $this->dbCon->query("DESCRIBE $tableName")->fetchAll(PDO::FETCH_OBJ);
		$cols = array();
		foreach($desc as $cd){
			$cols[] = $cd->Field;
		}
		return $cols;
	}
	
	/**
	 * Gets a PDO connection from the ini file
	 * @return PDO
	 */
	function PDOConnection(){
		$error = 'Error connecting to DB: ';
		// $iniFile = parse_ini_file(INI_FILE_PATH, true);
		$iniFile = parse_ini_file("db.ini", true);
		if($iniFile){

			$server = $_SERVER['SERVER_NAME'];

			if ($server) {
				$host = $iniFile[$server]['host'];
				$dbName = $iniFile[$server]['dbName'];
				$dbPort = $iniFile[$server]['dbPort'];
				$dbUser = $iniFile[$server]['dbUser'];
				$dbPass = $iniFile[$server]['dbPass'];
			} else {
				throw new Exception("$error host not found on ini file");
			}
			try{
				$dbInfo = "mysql:host=$host;port=$dbPort;dbname=$dbName";
				//echo $dbInfo, $dbUser, $dbPass;
				return new PDO($dbInfo, $dbUser, $dbPass, array(PDO::ERRMODE_EXCEPTION => true));
			} catch(PDOException $e){
				throw new Exception($error . $e->getMessage());
			}
		}
		else{
			throw new Exception("$error ini file not found");
		}
	}
}
?>