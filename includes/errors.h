/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavergn <mlavergn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:16:42 by mlavergn          #+#    #+#             */
/*   Updated: 2025/04/07 00:26:25 by mlavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

#define MAX_MAP_LINES 1024

# define VALID_ID "NSWAEO  \t"
# define VALID_MAPCHAR "10NESW  \n"
# define ERR_MALLOC "Malloc failed"
# define ERR_XPMSPACE "Has space in xpm name"
# define ERR_XPMSYNTAX "Texture syntax"
# define ERR_XPMDIR "XPM can't be a directory"
# define ERR_CUBEXT "Extension needs to be .cub"
# define ERR_OPEN   "Error while opening file"
# define ERR_ARGDIR "Argument can't be a directory"
# define ERR_NOARG "Argument needed !"
# define ERR_MULTI "Multiple declaration xpm"
# define ERR_UNKNOWNID "Invalid line in .cub file"
# define ERR_MISSINGTEXT "Texture missing"
# define ERR_EMPTYMAP "Empty line in map"
# define ERR_INVALIDMAPCHAR "Invalid char in map"
# define ERR_MAPEOF "Map line should be at the end of file"
#endif