<?php
?>

                            <div class="title">
                                 Welcome!
                            </div>
                            <div class="text">
                             <?php
                              $array = mysql_fetch_array(mysql_query("SELECT * FROM `content` WHERE `category` = 'welcome'"));
                              echo nl2br($array['text']);
                             ?>
                            </div>

                            <div class="title">
                                 News
                            </div>

                            <?php
                             $result = mysql_query("SELECT * FROM `news` ORDER BY `id` DESC LIMIT 4");
                             while($array = mysql_fetch_array($result))
                             {
                               ?>
                                <div class="date"><?php echo date("F jS, Y", $array['date']); ?></div>
                                <div class="newstitle"><?php echo $array['title']; ?> </div>
                                <div class="text">
                                 <?php echo $array['text']; ?>
                                </div>
                               <?php
                             }
                            ?>

