<?php
?>

<div class="title">
     Page Tool Demo
</div>

<div class="page_selector">

		<a href="#" class="prev_next">Previous</a> 
		
		<?php 
			for($i=10;$i<29;$i++)
			{
				if($i != 19)
				{
					echo '<a class="page" href="#">'.$i.'</a>'; 
				}else
				{
					echo '<span class="page_selected">'.$i.'</span>'; 
				}
			}
		?>
				
		 <a href="#" class="prev_next">Next</a> 
	</tr>
</table>