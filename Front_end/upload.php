<!DOCTYPE html>
<html>
	<head>
		<style>
			body {
				background-image: url('relax_m.jpg');
				background-size:     cover;
    			background-repeat:   no-repeat;
    			background-position: center center; 
    			background-color: black;
			}
			a {
				display: block;
				color: white;
				text-align: center;
				margin-top: 350px;
				font-size: 50px;
			}
			h2, h3 {
				text-align: center;
				color: white;
			}
		</style>
	</head>
	<body>
<?php
	if(isset($_FILES['fileToUpload']) && $_POST['op'] == "c"){
		$file_name = $_FILES['fileToUpload']['name'];
		$file_tmp = $_FILES['fileToUpload']['tmp_name'];
		move_uploaded_file($file_tmp,"/Library/WebServer/Documents/comp.txt");
		chmod("/Library/WebServer/Documents/comp.txt", 0777);
		chmod("/Library/WebServer/Documents/compi.bin", 0777);
		$start = microtime(true);
		$o = shell_exec("./compress.out"); 
		$end = microtime(true);
		
		echo "<a href = 'compi.bin' download > Compressed File </a>";
		echo "<h2>Time taken to compress : ".round($end - $start, 2)." seconds</h2>";
		$orig = filesize("/Library/WebServer/Documents/comp.txt");
		$comp = filesize("/Library/WebServer/Documents/compi.bin");
		echo "<h3>Original File Size : ".$orig."</h3>";
		echo "<h3>Compressed File Size : ".$comp."</h3>";
		echo "<h2>".round(((1 - ($comp / $orig)) * 100), 2)." % compression</h2>";
	}
	if(isset($_FILES['fileToUpload']) && $_POST['op'] == "d"){
		$file_name = $_FILES['fileToUpload']['name'];
		$file_tmp = $_FILES['fileToUpload']['tmp_name'];
		move_uploaded_file($file_tmp,"/Library/WebServer/Documents/compi.bin");
		chmod("/Library/WebServer/Documents/compi.bin", 0777);
		chmod("/Library/WebServer/Documents/decompi.txt", 0777);
		$start = microtime(true);
		$o = shell_exec("./decompress.out");
		$end = microtime(true);
		
		echo "<a href = 'decompi.txt' download > Decompressed File </a> ";
		echo "<h2>Time taken to decompress : ".round($end - $start, 2)." seconds</h2>";
		echo "<h3>Original File Size : ".filesize("/Library/WebServer/Documents/compi.bin")."</h3>";
		echo "<h3>Decompressed File Size : ".filesize("/Library/WebServer/Documents/decompi.txt")."</h3>";
	}
?>
	</body>
</html>