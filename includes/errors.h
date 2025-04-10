/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:16:42 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/10 14:06:18 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define MAX_MAP_LINES 1024

# define VALID_ID "NSWAEO  \t"
# define VALID_MAPCHAR "10NESW  \n"
# define PLAYERCHAR "NESW"
# define VALID_STARTMAP "1 "
# define ERR_MALLOC "Malloc failed"
# define ERR_XPMSPACE "Has space in xpm name"
# define ERR_XPMSYNTAX "Texture syntax"
# define ERR_XPMDIR "XPM can't be a directory"
# define ERR_CUBEXT "Extension needs to be .cub"
# define ERR_OPEN   "Error while opening file"
# define ERR_ARGDIR "Argument can't be a directory"
# define ERR_NOARG "Fix arguments"
# define ERR_MULTI "Multiple declaration xpm"
# define ERR_UNKNOWNID "Invalid line in .cub file"
# define ERR_MISSINGTEXT "Invalid .cub file"
# define ERR_EMPTYMAP "Empty line in map"
# define ERR_INVALIDMAPCHAR "Invalid char in map"
# define ERR_MAPEOF "Map line should be at the end of file"
# define ERR_MULTPLAYER "Multiple players on the map"
# define ERR_NOPLAYER "No player on the map"
# define ERR_PLAYERSTUCK "Player is stuck in spawn"
# define ERR_MAPUNCLOSED "Map is not closed"
# define ERR_TABMAP "Tab not allowed in map"
# define ERR_RGBNEG "RGB values can't be negative"
# define ERR_RGBCHAR "RGB must be numbers only"
#endif