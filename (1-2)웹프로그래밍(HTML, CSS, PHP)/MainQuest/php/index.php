<!DOCTYPE HTML>
<html>
    <head>
        <meta charset="utf-8">
        <link rell="stylesheet" type="text/css" href="localhost"
    
    </head>
    <body>
        <header>
            <h1><a href="http://localhost/">JavaScript</a></h1>
        </header>
        <nav>
            <ol>
                <?php 
                    echo file_get_contents("list.txt");
                
                ?>
            </ol>
        </nav>
        <div id="control">
            <input type ="button" value ="white" onclick="document.getElemenByld('target').className='white'"/>
            <input type="button" value="black" onclick="document.getElemenByld('target').className='black'"/>
        </div>
        <article>
            <?php 
            if(empty($_GET["id"]) == false)//empty는 값이 없는걸 판별
            {
                echo file_get_contents($_GET["id"]."txt");
            }
            
            ?>
        </article>


    </body>
</html>